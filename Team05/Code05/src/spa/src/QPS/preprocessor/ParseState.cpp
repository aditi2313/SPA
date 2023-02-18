#include <memory>
#include <utility>

#include "ParseState.h"

#include "QPS/models/PQL.h"
#include "common/Exceptions.h"
#include "models/Entity.h"

namespace qps {
// design-entity synonym (',' synonym)* ';'
void DeclarationParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
  if (itr == tokens.end() || !PQL::is_entity_name(*itr)) ThrowException();

  EntityName entity_name = *itr;
  bool has_set_one_synonym = false;
  itr++;
  while (itr != tokens.end() && *itr != ";") {
    if (!PQL::is_ident(*itr)) ThrowException();

    query->declare_synonym(*itr, entity_name);
    has_set_one_synonym = true;
    itr++;
    if (itr != tokens.end() && *itr == ",") {
      itr++;  // read in next synonym
    }
  }

  if (!has_set_one_synonym) ThrowException();
  if (itr == tokens.end()) ThrowException();
  itr++;
}

// synonym
void SelectParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSynGrammar) {
      query->add_selected_synonym(*itr);
    }
    itr++;
    grammar_itr++;
  }

  if (grammar_itr != grammar_.end()) ThrowException();
}

// 'such' 'that' relRef
// e.g. relRef = Modifies(6, v)
void SuchThatParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
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

  if (grammar_itr != grammar_.end()) ThrowException();

  query->add_clause(Clause::CreateClause(
      rel_ident,
      std::move(arguments.at(0)), std::move(arguments.at(1))));
}

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
void PatternParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
  auto grammar_itr = grammar_.begin();
  std::vector<ArgumentPtr> arguments;
  while (itr != tokens.end() && grammar_itr != grammar_.end()) {
    if (!PQL::CheckGrammar(*itr, *grammar_itr)) {
      ThrowException();
    }
    if (*grammar_itr == PQL::kSynGrammar
        || *grammar_itr == PQL::kArgumentGrammar
        || *grammar_itr == PQL::kExprGrammar) {
      arguments.push_back(query->CreateArgument(*itr));
    }
    itr++;
    grammar_itr++;
  }

  if (grammar_itr != grammar_.end()) ThrowException();

  query->add_clause(Clause::CreateClause(
      PQL::kModifiesRelId,
      std::move(arguments.at(0)->Copy()),
      std::move(arguments.at(1))));
  query->add_clause(Clause::CreateClause(
      PQL::kPatternRelId,
      std::move(arguments.at(0)),
      std::move(arguments.at(2))));
}

ParseState::~ParseState() = default;
}  // namespace qps
