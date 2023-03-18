#pragma once

#include <utility>
#include <string>

#include "RecursiveParseState.h"
#include "QPS/factories/MasterArgumentFactory.h"

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
    size_t kNumGrammar = 10;
    // Need to do reserve to ensure that iterators (i.e kRecurseBegin)
    // are not invalidated after modifying the vector
    grammar_.reserve(kNumGrammar);

    // 'pattern'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kPatternToken),
            Grammar::kEmptyAction));

    // syn-assign | syn-while | syn-if
    grammar_.emplace_back(
        Grammar(
            Grammar::kSynCheck,
            [&](QueryPtr &query) {
              if (!query->is_synonym_name_declared(*itr_)) {
                throw PqlSemanticErrorException(
                    "Synonym name in Pattern clause has not been declared");
              }
              EntityType entity_type =
                  query->get_declared_synonym_entity_type(*itr_);
              arg1_ =
                  master_argument_factory_.CreateSynonym(*itr_, entity_type);
              pattern_clause_type_ = ClauseType::kPatternUndetermined;
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
              if (!Grammar::kWildcardCheck(*itr_)) {
                // Not a wildcard, must be pattern-assign
                pattern_clause_type_ = ClauseType::kPatternAssign;
              }
              arg3_ = master_argument_factory_.CreateExpressionSpec(*itr_);
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
                if (pattern_clause_type_ == ClauseType::kPatternAssign) {
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
              pattern_clause_type_ = ClauseType::kPatternIf;
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
              EntityType entity_type = SynonymArg::get_entity_type(arg1_);
              if (pattern_clause_type_ == ClauseType::kPatternIf
                  && entity_type != EntityType::kIf)
                throw PqlSemanticErrorException(
                    "Pattern-if clause does not start with a syn-if");

              if (entity_type == EntityType::kAssign)
                pattern_clause_type_ = ClauseType::kPatternAssign;

              if (entity_type == EntityType::kWhile)
                pattern_clause_type_ = ClauseType::kPatternWhile;

              if (pattern_clause_type_ == ClauseType::kPatternUndetermined) {
                throw PqlSemanticErrorException(
                    "Unsupported synonym in Pattern clause");
              }

              if (entity_type == EntityType::kAssign) {
                // Need to create two clauses
                query->add_clause(master_clause_factory_.Create(
                    ClauseType::kModifies,
                    std::move(arg1_->Copy()),
                    std::move(arg2_)));
                query->add_clause(master_clause_factory_.Create(
                    ClauseType::kPatternAssign,
                    std::move(arg1_),
                    std::move(arg3_)));
                return;
              }

              query->add_clause(master_clause_factory_.Create(
                  pattern_clause_type_,
                  std::move(arg1_),
                  std::move(arg2_)));
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
  ClauseType pattern_clause_type_;
};
}  // namespace qps
