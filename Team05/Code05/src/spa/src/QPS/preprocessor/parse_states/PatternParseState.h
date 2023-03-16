#pragma once

#include <utility>

#include "RecursiveParseState.h"

namespace qps {
extern MasterClauseFactory master_clause_factory_;
extern MasterArgumentFactory master_argument_factory_;

// pattern ( 'and' pattern )*
// pattern: 'pattern' syn-assign '(' entRef ',' expression-spec ')'
// expression-spec: "expr" | _"expr"_ | _
class PatternParseState : public RecursiveParseState {
 public:
  PatternParseState()
      : RecursiveParseState(PQL::kPatternToken,
                            PQL::kAndToken) {
    size_t kNumGrammar = 8;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // 'pattern'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kPatternToken),
            Grammar::kEmptyAction));
    kRecurseBegin = --grammar_.end();  // Recurse from here

    // syn-assign
    grammar_.emplace_back(
        Grammar(
            Grammar::kSynCheck,
            [&](QueryPtr &query) {
              arg1_ = master_argument_factory_.CreateSynonym(*itr_);
            }));

    // '('
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kOpenBktToken),
            Grammar::kEmptyAction));

    // argument
    grammar_.emplace_back(
        Grammar(
            Grammar::kArgumentCheck,
            [&](QueryPtr &query) {
              arg2_ = master_argument_factory_.CreateEntRef(*itr_);
            }));

    // ','
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kCommaToken),
            Grammar::kEmptyAction));

    // expression-spec
    grammar_.emplace_back(
        Grammar(
            Grammar::kExprCheck,
            [&](QueryPtr &query) {
              arg3_ = master_argument_factory_.CreateExpressionSpec(*itr_);
            }));

    // ')'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kCloseBktToken),
            [&](QueryPtr &query) {
              if (arg1_ == nullptr || arg2_ == nullptr || arg3_ == nullptr) {
                ThrowException();
              }
              query->add_clause(master_clause_factory_.Create(
                  PQL::kModifiesRelName,
                  std::move(arg1_->Copy()),
                  std::move(arg2_)));
              query->add_clause(master_clause_factory_.Create(
                  PQL::kPatternRelName,
                  std::move(arg1_),
                  std::move(arg3_)));
            }));

    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.emplace_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in pattern";
  }

 private:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  ArgumentPtr arg3_;
};
}  // namespace qps
