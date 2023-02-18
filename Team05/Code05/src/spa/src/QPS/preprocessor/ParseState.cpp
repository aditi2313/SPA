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

// synonym (',' synonym)*
void SynonymParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
  // TODO(JL): Support multiple synonyms selection after
  // requirement is introduced
  if (itr == tokens.end() || *itr != "Select" && *itr != ",") ThrowException();
  itr++;
  if (!PQL::is_ident(*itr)) ThrowException();
  query->add_selected_synonym(*itr);
  itr++;
}

// 'such' 'that' relRef
// e.g. relRef = Modifies(6, v)
void SuchThatParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
  if (itr == tokens.end()) ThrowException();
  if (*itr++ != "such") ThrowException();
  if (*itr++ != "that") ThrowException();

  std::string rel_ident = *itr++;
  if (*itr++ != "(") ThrowException();
  ArgumentPtr arg1 = query->CreateArgument(*itr++);
  if (*itr++ != ",") ThrowException();
  ArgumentPtr arg2 = query->CreateArgument(*itr++);
  if (*itr != ")") ThrowException();

  query->add_clause(Clause::CreateClause(
      rel_ident, std::move(arg1), std::move(arg2)));

  itr++;
}

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
void PatternParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    QueryPtr &query) {
  if (itr == tokens.end()) ThrowException();
  if (*itr++ != PQL::kPatternRelId) ThrowException();
  ArgumentPtr arg1 = query->CreateArgument(*itr);
  ArgumentPtr arg1_copy = query->CreateArgument(*itr++);
  if (*itr++ != "(") ThrowException();
  ArgumentPtr arg2 = query->CreateArgument(*itr++);
  if (*itr++ != ",") ThrowException();
  ArgumentPtr arg3 = query->CreateArgument(*itr++);
  if (*itr != ")") ThrowException();

  query->add_clause(Clause::CreateClause(
      PQL::kModifiesRelId, std::move(arg1_copy), std::move(arg2)));
  query->add_clause(Clause::CreateClause(
      PQL::kPatternRelId, std::move(arg1), std::move(arg3)));
  itr++;
}

ParseState::~ParseState() = default;
}  // namespace qps
