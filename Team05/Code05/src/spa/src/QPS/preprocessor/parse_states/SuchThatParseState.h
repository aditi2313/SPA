#pragma once

#include <utility>

#include "RecursiveParseState.h"
#include "QPS/factories/Export.h"

namespace qps {
extern MasterClauseFactory master_clause_factory_;
extern MasterArgumentFactory master_argument_factory_;

// 'such' 'that' relCond
// relCond: relRef ('and' relRef)*
// relRef
class SuchThatParseState : public RecursiveParseState {
 public:
  SuchThatParseState()
      : RecursiveParseState(PQL::kSuchToken,
                            PQL::kAndToken) {
    size_t kNumGrammar = 9;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // 'such'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kSuchToken),
            Grammar::kEmptyAction));
    // 'that'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kThatToken),
            Grammar::kEmptyAction));

    // relRef
    grammar_.emplace_back(
        Grammar(
            Grammar::kRelRefCheck,
            [&](QueryPtr &query) {
              rel_name_ = *itr_;
            }));
    kRecurseBegin = --grammar_.end();  // Recurse from here

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
              arg1_ = master_argument_factory_.CreateEntOrStmtRef(*itr_);
            }));

    // ','
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kCommaToken),
            Grammar::kEmptyAction));

    // argument
    grammar_.emplace_back(
        Grammar(
            Grammar::kArgumentCheck,
            [&](QueryPtr &query) {
              arg2_ = master_argument_factory_.CreateEntOrStmtRef(*itr_);
            }));

    // ')'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kCloseBktToken),
            [&](QueryPtr &query) {
              if (arg1_ == nullptr || arg2_ == nullptr) ThrowException();
              query->add_clause(master_clause_factory_.Create(
                  PQL::get_clause_type(rel_name_),
                  std::move(arg1_),
                  std::move(arg2_)));
            }));

    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.emplace_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in such-that";
  }

 private:
  RelName rel_name_;
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
};
}  // namespace qps
