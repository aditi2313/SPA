#include "ParseState.h"

#include <memory>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/models/Entity.h"

namespace qps {
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
    }
    itr++;
    grammar_itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// tuple | BOOLEAN
void SelectParseState::Parse(const std::vector<std::string> &tokens,
                             parse_position &itr, QueryPtr &query) {
  TupleParseState tuple_parse_state;

  auto grammar_itr = grammar_.begin();
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSelectGrammar) {
      // if BOOLEAN is a declared synonym name,
      // we treat it as a synonym (synonym takes precedence)
      if (*itr == PQL::kBooleanSelect
          && !query->is_synonym_name_declared(*itr)) {
        query->set_boolean_query_to_true();
      } else if (*itr == PQL::kTupleSelectOpen) {
        tuple_parse_state.Parse(tokens, itr, query);
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
    }
    itr++;
    grammar_itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();
}

// 'such' 'that' relRef
// e.g. relRef = Modifies(6, v)
void SuchThatParseState::Parse(const std::vector<std::string> &tokens,
                               parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  std::string rel_ident;
  std::vector<ArgumentPtr> arguments;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kRelRefGrammar) {
      rel_ident = *itr;
    }
    if (*grammar_itr == PQL::kArgumentGrammar) {
      arguments.push_back(query->CreateArgument(*itr));
    }
    itr++;
    grammar_itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();

  query->add_clause(Clause::CreateClause(
      rel_ident,
      std::move(arguments.at(0)),
      std::move(arguments.at(1))));
}

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
void PatternParseState::Parse(const std::vector<std::string> &tokens,
                              parse_position &itr, QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  std::vector<ArgumentPtr> arguments;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSynGrammar ||
        *grammar_itr == PQL::kArgumentGrammar ||
        *grammar_itr == PQL::kExprGrammar) {
      arguments.push_back(query->CreateArgument(*itr));
    }
    itr++;
    grammar_itr++;
  }

  if (!IsComplete(grammar_itr)) ThrowException();

  query->add_clause(Clause::CreateClause(PQL::kModifiesRelId,
                                         std::move(arguments.at(0)->Copy()),
                                         std::move(arguments.at(1)->Copy())));
  query->add_clause(Clause::CreateClause(PQL::kPatternRelId,
                                         std::move(arguments.at(0)->Copy()),
                                         std::move(arguments.at(2))));
}

ParseState::~ParseState() = default;
}  // namespace qps
