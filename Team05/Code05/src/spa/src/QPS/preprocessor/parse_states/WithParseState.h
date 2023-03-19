#pragma once

#include <utility>
#include <vector>
#include <string>

#include "RecursiveParseState.h"
#include "QPS/factories/MasterClauseFactory.h"
#include "QPS/models/grammar/Export.h"

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

    // ref: Ident | Integer | AttrRef
    grammar_.emplace_back(
        Grammar(
            Grammar::kRefCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              CreateRef(tokens, query, arg1_);
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
              CreateRef(tokens, query, arg2_);

              // Create clause
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
  // ref: " Ident " | Integer | AttrRef
  inline void CreateRef(
      const std::vector<std::string> &tokens,
      QueryPtr &query,
      ArgumentPtr &arg) {
    AttrRefGrammar attr_ref_grammar(tokens, query, itr_, arg);
    bool is_attr_ref = attr_ref_grammar.Parse();
    if (is_attr_ref) return;

    IdentArgGrammar ident_arg_grammar(tokens, query, itr_, arg);
    bool is_ident_arg = ident_arg_grammar.Parse();
    if (is_ident_arg) return;

    arg = master_argument_factory_.CreateIntegerArg(*itr_);
  }

  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
};
}  // namespace qps
