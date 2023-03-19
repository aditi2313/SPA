#pragma once

#include <string>

#include "RecursiveParseState.h"

namespace qps {
// design-entity synonym (',' synonym)* ';'
class DeclarationParseState : public RecursiveParseState {
 public:
  DeclarationParseState()
      : RecursiveParseState("",
                            PQL::kCommaToken) {
    size_t kNumGrammar = 4;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // design-entity
    grammar_.emplace_back(
        Grammar(
            Grammar::kDesignEntityCheck,
            [&](QueryPtr &query,
                const std::vector<std::string> &tokens) {
              declared_entity_name_ = *itr_;
            }));

    // synonym
    grammar_.emplace_back(
        Grammar(
            Grammar::kSynCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              query->declare_synonym(
                  *itr_, PQL::get_entity_type(declared_entity_name_));
            }));
    kRecurseBegin = --grammar_.end();  // Recurse from here

    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    // ;
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kSemicolonToken),
            Grammar::kEmptyAction));

    end_states_.emplace_back(grammar_.end());
    kExceptionMessage = "Invalid PQL syntax in declaration";
  }

  inline bool is_transition_keyword(std::string token) override {
    return PQL::is_entity_name(token);
  }

 private:
  EntityName declared_entity_name_;
};
}  // namespace qps
