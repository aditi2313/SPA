#pragma once

#include <vector>
#include <utility>

#include "RecursiveParseState.h"

namespace qps {

// pattern ( 'and' pattern )*
// pattern: assign | while | if
// assign: syn-assign '(' entRef ',' expression-spec ')'
// while: syn-while '(' entRef ',' '_' ')'
// if: syn-if '(' entRef ',' '_' ',' '_' ')'
// expression-spec: '"' expr'"' | '_' '"' expr '"' '_' | '_'
class PatternParseState : public RecursiveParseState {
 public:
  PatternParseState()
      : RecursiveParseState(PQL::kPatternToken,
                            PQL::kAndToken) {
    InitializeAssignGrammar();
    InitializeIfGrammar();
    InitializeWhileGrammar();

    size_t kNumGrammar = 3;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // 'pattern'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kPatternToken),
            Grammar::kEmptyAction));
    kRecurseBegin = --grammar_.end();  // Recurse from here

    // syn-assign | syn-while | syn-if
    grammar_.emplace_back(
        Grammar(
            Grammar::kSynCheck,
            [&](QueryPtr &query) {
              arg1_ = query->CreateArgument(*itr_);
              EntityName entity_name = SynonymArg::get_entity_name(arg1_);
              if (entity_name == PQL::kWhileEntityName) {
                // Is While
                grammar_itr_ = while_grammar_.begin();
              } else if (entity_name == PQL::kIfEntityName) {
                // Is If
                grammar_itr_ = if_grammar_.begin();
              } else {
                // Is Assign
                grammar_itr_ = assign_grammar_.begin();
                // Note: Validator will validate if this is syn-assign
                // and throw semantic error accordingly
              }
            }));

    // Recurse (if needed)
    grammar_.emplace_back(
        RecursiveParseState::CreateRecurseGrammar(*this));

    // Resume from here after competing assign/while/if grammar_
    saved_grammar_itr_pos_ = --grammar_.end();

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.emplace_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in pattern";
  }

 private:
  void InitializeAssignGrammar();
  void InitializeIfGrammar();
  void InitializeWhileGrammar();

  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  ArgumentPtr arg3_;

  std::vector<Grammar> assign_grammar_;
  std::vector<Grammar> while_grammar_;
  std::vector<Grammar> if_grammar_;

  GrammarItr saved_grammar_itr_pos_;
};
}  // namespace qps
