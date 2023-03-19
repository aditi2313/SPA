#pragma once

#include <utility>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "RecursiveParseState.h"
#include "QPS/factories/MasterArgumentFactory.h"
#include "QPS/models/grammar/Export.h"

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
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg1_ = master_argument_factory_.Create(
                  ArgumentType::kSynonymArg, *itr_);
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
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              IdentArgGrammar ident_arg_grammar(tokens, query, itr_, arg2_);
              bool is_ident_arg = ident_arg_grammar.Parse();
              if (!is_ident_arg) {
                arg2_ = master_argument_factory_.Create(
                    {ArgumentType::kWildcard, ArgumentType::kSynonymArg},
                    *itr_);
              }
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
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              if (!Grammar::kWildcardCheck(*itr_)) {
                // Not a wildcard, must be pattern-assign
                pattern_clause_type_ = ClauseType::kPatternAssign;
              }
              CreateExpressionSpec(tokens, query, arg3_);
            }));

    // ',' | skip to ')'
    grammar_.emplace_back(
        Grammar(
            [](std::string token) {
              return token == PQL::kCommaToken || token == PQL::kCloseBktToken;
            },
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
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
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              // Must be if-type
              pattern_clause_type_ = ClauseType::kPatternIf;
            }));

    // ')'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kCloseBktToken),
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              if (arg1_ == nullptr || arg2_ == nullptr || arg3_ == nullptr) {
                ThrowException();
              }
              CreatePatternClause(query);
            }));

    // Recurse (if needed)
    grammar_.emplace_back(RecursiveParseState::CreateRecurseGrammar(*this));

    end_states_.emplace_back(grammar_.end());
    // Allow state to end without recursing
    end_states_.emplace_back(prev(grammar_.end()));
    kExceptionMessage = "Invalid PQL syntax in pattern";
  }

 private:
  inline void CreateExpressionSpec(
      const std::vector<std::string> &tokens,
      QueryPtr &query,
      ArgumentPtr &arg) {
    WildcardExprGrammar wildcard_expr_grammar(
        tokens, query, itr_, arg);
    bool is_wildcard_expr = wildcard_expr_grammar.Parse();
    if (is_wildcard_expr) return;

    ExactExprGrammar exact_expr_grammar(
        tokens, query, itr_, arg);
    bool is_exact_expr = exact_expr_grammar.Parse();
    if (is_exact_expr) return;

    arg = master_argument_factory_.Create(ArgumentType::kWildcard, "ß");
  }

  inline void CreatePatternClause(
      QueryPtr &query) {
    if (!GetPatternClauseType(query)) {
      has_semantic_error_ = true;
      return;
    }

    if (pattern_clause_type_ == ClauseType::kPatternAssign) {
      // Need to create two clauses
      query->add_clause(master_clause_factory_.Create(
          ClauseType::kModifies,
          std::move(arg1_->Copy()),
          std::move(arg2_)));
      query->add_clause(master_clause_factory_.Create(
          ClauseType::kPatternAssign,
          std::move(arg1_),
          std::move(arg3_)));
    } else {
      // kPatternIf or kPatternWhile
      query->add_clause(master_clause_factory_.Create(
          pattern_clause_type_,
          std::move(arg1_),
          std::move(arg2_)));
    }
  }

  // Returns false if there is no valid pattern clause type
  // match - indicating that there is a SemanticError
  inline bool GetPatternClauseType(QueryPtr &query) {
    auto syn_arg = dynamic_cast<SynonymArg *>(arg1_.get());
    if (!query->is_synonym_name_declared(syn_arg->get_syn_name())) {
      return false;
    }

    EntityType entity_type = query->get_declared_synonym_entity_type(
        syn_arg->get_syn_name());

    if (!kEntityTypeToClauseTypeMap.count(entity_type)) {
      // Not assign or while or if
      return false;
    }

    if (pattern_clause_type_ == ClauseType::kPatternUndetermined
        && entity_type == EntityType::kIf) {
      // Undetermined can only be Assign or While
      return false;
    }

    pattern_clause_type_ =
        pattern_clause_type_ == ClauseType::kPatternUndetermined
        ? kEntityTypeToClauseTypeMap.at(entity_type)
        : pattern_clause_type_;

    if (pattern_clause_type_ !=
        kEntityTypeToClauseTypeMap.at(entity_type)) {
      // Mismatch between EntityType and ClauseType
      return false;
    }

    syn_arg->set_entity_type(entity_type);
    return true;
  }

  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  ArgumentPtr arg3_;
  ClauseType pattern_clause_type_;

  inline static std::unordered_map<EntityType, ClauseType>
      kEntityTypeToClauseTypeMap{
      {EntityType::kAssign, ClauseType::kPatternAssign},
      {EntityType::kIf, ClauseType::kPatternIf},
      {EntityType::kWhile, ClauseType::kPatternWhile}
  };
};
}  // namespace qps
