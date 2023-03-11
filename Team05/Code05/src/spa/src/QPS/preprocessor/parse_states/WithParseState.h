#pragma once

#include <utility>

#include "RecursiveParseState.h"
#include "QPS/factories/MasterClauseFactory.h"

namespace qps {
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
            [&](QueryPtr &query) {
              arg1_ = query->CreateArgument(*itr_);
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
            [&](QueryPtr &query) {
              arg2_ = query->CreateArgument(*itr_);
              if (arg1_ == nullptr || arg2_ == nullptr) ThrowException();
              auto with_clause = master_clause_factory_.Create(
                  PQL::kWithRelName,
                  std::move(arg1_),
                  std::move(arg2_));
              query->add_clause(with_clause);
            }));


    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.push_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in with";
  }

 private:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
};
}  // namespace qps
