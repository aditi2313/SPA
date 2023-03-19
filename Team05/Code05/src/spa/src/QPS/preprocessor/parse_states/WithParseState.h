#pragma once

#include <utility>

#include "RecursiveParseState.h"
#include "QPS/factories/MasterClauseFactory.h"

namespace qps {
extern MasterArgumentFactory master_argument_factory_;
extern MasterClauseFactory master_clause_factory_;

// 'with' attrCompare '(' and ',' attrCompare ')'
// attrCompare: ref '=' ref
// attrRef: "IDENT" | INTEGER | synonym.attrName
// attrName: varName | procName | value | stmt#
class WithParseState : public RecursiveParseState {
 public:
  WithParseState()
      : RecursiveParseState(PQL::kWithToken,
                            PQL::kAndToken) {
    size_t kNumGrammar = 5;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // 'with'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kWithToken),
            Grammar::kEmptyAction));

    // ref
    grammar_.emplace_back(
        Grammar(
            Grammar::kRefCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg1_ = master_argument_factory_.CreateRef(*itr_);
            }));
    kRecurseBegin = --grammar_.end();  // Recurse from here


    // '='
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kEqualToken),
            Grammar::kEmptyAction));

    // ref
    grammar_.emplace_back(
        Grammar(
            Grammar::kRefCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg2_ = master_argument_factory_.CreateRef(*itr_);
              if (arg1_ == nullptr || arg2_ == nullptr) ThrowException();
              auto with_clause = master_clause_factory_.Create(
                  ClauseType::kWith,
                  std::move(arg1_),
                  std::move(arg2_));
              query->add_clause(with_clause);
            }));


    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.emplace_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in with";
  }

 private:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
};
}  // namespace qps
