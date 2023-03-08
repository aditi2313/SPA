#include "ParseState.h"

#include <memory>
#include <utility>

#include "QPS/factories/MasterClauseFactory.h"
#include "QPS/models/Entity.h"
#include "QPS/models/PQL.h"

namespace qps {
extern MasterClauseFactory master_clause_factory_;

// design-entity synonym (',' synonym)* ';'
void DeclarationParseState::Parse(const std::vector<std::string> &tokens,
                                  parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  EntityName entity_name;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kDesignEntityGrammar) {
      entity_name = *itr;
    }
    if (*grammar_itr == PQL::kSynGrammar) {
      query->declare_synonym(*itr, entity_name);
    }
    if (*grammar_itr == PQL::kRecurseGrammar) {
      Recurse(itr, grammar_itr);
    } else {
      grammar_itr++;
    }
    itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// tuple | BOOLEAN
void SelectParseState::Parse(const std::vector<std::string> &tokens,
                             parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSelectGrammar) {
      // if BOOLEAN is a declared synonym name,
      // we treat it as a synonym (synonym takes precedence)
      if (*itr == PQL::kBooleanSelect &&
          !query->is_synonym_name_declared(*itr)) {
        query->set_boolean_query_to_true();
      } else if (*itr == PQL::kTupleSelectOpen) {
        tuple_parse_state_.Parse(tokens, itr, query);
        itr--;
      } else {
        query->add_selected_synonym(*itr);
      }
    }
    itr++;
    grammar_itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// '<' elem ( ',' elem )* '>'
void TupleParseState::Parse(const std::vector<std::string> &tokens,
                            parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSynGrammar) {
      query->add_selected_synonym(*itr);
    }
    if (*grammar_itr == PQL::kRecurseGrammar) {
      Recurse(itr, grammar_itr);
    } else {
      grammar_itr++;
    }
    itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// 'such' 'that' relCond
// relCond: relRef ( 'and' relRef )*
// e.g. relRef = Modifies(6, v)
void SuchThatParseState::Parse(const std::vector<std::string> &tokens,
                               parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  std::string rel_ident;
  ArgumentPtr arg1, arg2;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kRelRefGrammar) {
      rel_ident = *itr;
    }
    if (*grammar_itr == PQL::kArgumentGrammar) {
      if (arg1 == nullptr) {
        arg1 = query->CreateArgument(*itr);
      } else {
        arg2 = query->CreateArgument(*itr);
      }
    }
    if (grammar_itr + 1 != grammar_.end() &&
        *(grammar_itr + 1) == PQL::kRecurseGrammar) {
      if (arg1 == nullptr || arg2 == nullptr) {
        ThrowException();
      }
      query->add_clause(master_clause_factory_.Create(
          rel_ident, std::move(arg1), std::move(arg2)));
    }
    if (*grammar_itr == PQL::kRecurseGrammar) {
      Recurse(itr, grammar_itr);
    } else {
      grammar_itr++;
    }
    itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// pattern ( 'and' pattern )*
// pattern: 'pattern' syn-assign '(' entRef ',' expression-spec ')'
void PatternParseState::Parse(const std::vector<std::string> &tokens,
                              parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  ArgumentPtr arg1, arg2, arg3;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSynGrammar) {
      arg1 = query->CreateArgument(*itr);
    }
    if (*grammar_itr == PQL::kArgumentGrammar) {
      arg2 = query->CreateArgument(*itr);
    }
    if (*grammar_itr == PQL::kExprGrammar) {
      arg3 = query->CreateArgument(*itr);
    }
    if (grammar_itr + 1 != grammar_.end() &&
        *(grammar_itr + 1) == PQL::kRecurseGrammar) {
      if (arg1 == nullptr || arg2 == nullptr || arg3 == nullptr) {
        ThrowException();
      }
      query->add_clause(master_clause_factory_.Create(
          PQL::kModifiesRelName, std::move(arg1->Copy()), std::move(arg2)));
      query->add_clause(master_clause_factory_.Create(
          PQL::kPatternRelName, std::move(arg1), std::move(arg3)));
    }

    if (*grammar_itr == PQL::kRecurseGrammar) {
      Recurse(itr, grammar_itr);
    } else {
      grammar_itr++;
    }
    itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// 'with' attrCompare '(' and ',' attrCompare ')'
// attrCompare: attrRef = attrRef
// attrRef: "IDENT" | INTEGER | synonym.attrName
// attrName: varName | procName | value | stmt#
void WithParseState::Parse(const std::vector<std::string> &tokens,
                           parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  ArgumentPtr arg1, arg2;
  PQL::AttrName LHS_attr_name, RHS_attr_name;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }

    if (*grammar_itr == PQL::kRefGrammar) {
      std::string arg = *itr;
      if (PQL::is_attr_ref(*itr)) {
        auto [syn, attr_name] = PQL::split_rel_ref(*itr);
        arg = syn;
        if (arg1 == nullptr) {
          LHS_attr_name = attr_name;
        } else {
          RHS_attr_name = attr_name;
        }
      }

      if (arg1 == nullptr) {
        arg1 = query->CreateArgument(arg);
      } else {
        arg2 = query->CreateArgument(arg);
      }
    }

    if (*(grammar_itr + 1) == PQL::kRecurseGrammar) {
      if (arg1 == nullptr || arg2 == nullptr) {
        ThrowException();
      }
      auto with_clause = master_clause_factory_.Create(
          PQL::kWithRelName,
          std::move(arg1),
          std::move(arg2));
      query->add_clause(with_clause);

      // Reset attr_name
      LHS_attr_name.clear();
      RHS_attr_name.clear();
    }

    if (*grammar_itr == PQL::kRecurseGrammar) {
      Recurse(itr, grammar_itr);
    } else {
      grammar_itr++;
    }
    itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

ParseState::~ParseState() = default;
}  // namespace qps
