#pragma once

#include <string>

#include "ParseState.h"

namespace qps {
// 'Select' tuple | BOOLEAN
class SelectParseState : public RecursiveParseState {
 public:
  SelectParseState() : RecursiveParseState(
      PQL::kSelectToken,
      PQL::kCommaToken) {
    size_t kNumGrammar = 6;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // 'Select'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kSelectToken),
            Grammar::kEmptyAction));

    // tuple | BOOLEAN
    grammar_.emplace_back(
        Grammar(
            [](std::string token) {
              return Grammar::kTupleCheck(token)
                  || Grammar::kBooleanCheck(token);
            },
            [&](QueryPtr &query) {
              if (Grammar::kBooleanCheck(*itr_) &&
                  !query->is_synonym_name_declared(*itr_)) {
                query->set_boolean_query_to_true();
                grammar_itr_ = grammar_.end();
              } else if (*itr_ == PQL::kTupleOpenBktToken) {
                itr_--;
              } else {
                query->add_selected_elem(*itr_);
                grammar_itr_ = grammar_.end();
              }
            }));

    // '<'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kTupleOpenBktToken),
            Grammar::kEmptyAction));

    // elem
    grammar_.emplace_back(
        Grammar(
            Grammar::kElemCheck,
            [&](QueryPtr &query) {
              query->add_selected_elem(*itr_);
            }));
    kRecurseBegin = --grammar_.end();  // Recurse from here

    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    // '>'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kTupleCloseBktToken),
            Grammar::kEmptyAction));

    end_states_.emplace_back(grammar_.end());
    kExceptionMessage = "Invalid PQL syntax in select-tuple|boolean";
  }
};
}  // namespace qps
