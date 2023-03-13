#pragma once

#include <vector>
#include <utility>
#include <string>

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
    size_t kNumGrammar = 10;
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
              pattern_clause_type_ = PatternClauseType::kPatternUndetermined;
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
              arg2_ = query->CreateArgument(*itr_);
            }));

    // ','
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kCommaToken),
            Grammar::kEmptyAction));

    // wildcard | expression-spec
    grammar_.emplace_back(
        Grammar(
            Grammar::kExprCheck,
            [&](QueryPtr &query) {
              if (!Grammar::kWildcardCheck(*itr_)) {
                // Not a wildcard, must be pattern-assign
                pattern_clause_type_ = PatternClauseType::kPatternAssign;
              }
              arg3_ = query->CreateArgument(*itr_);
            }));

    // ',' | skip to ')'
    grammar_.emplace_back(
        Grammar(
            [](std::string token) {
              return token == PQL::kCommaToken || token == PQL::kCloseBktToken;
            },
            [&](QueryPtr &query) {
              if (*itr_ == PQL::kCloseBktToken) {
                grammar_itr_++;  // Skip to close bkt
                itr_--;  // Don't consume token
              } else {
                // Must be comma
                if (pattern_clause_type_ == PatternClauseType::kPatternAssign) {
                  // This means that the second argument was not a wildcard.
                  // Doesn't syntactically match with syn-if(entRef, _, _)
                  ThrowException();
                }
              }
            }));

    // '_' (Optional)
    grammar_.emplace_back(
        Grammar(
            Grammar::kWildcardCheck,
            [&](QueryPtr &query) {
              // Must be if-type
              pattern_clause_type_ = PatternClauseType::kPatternIf;
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
    grammar_.emplace_back(
        RecursiveParseState::CreateRecurseGrammar(*this));

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.emplace_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in pattern";
  }

 private:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  ArgumentPtr arg3_;
  PatternClauseType pattern_clause_type_;
};
}  // namespace qps
