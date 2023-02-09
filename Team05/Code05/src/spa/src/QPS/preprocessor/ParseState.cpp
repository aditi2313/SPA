#include <memory>
#include <utility>

#include "ParseState.h"

#include "QPS/models/PQL.h"
#include "common/Exceptions.h"
#include "models/Entity.h"

namespace qps {
// design-entity synonym (',' synonym)* ';'
std::unique_ptr<Query> DeclarationParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    std::unique_ptr<Query> query) {
  if (itr == tokens.end() || !PQL::is_entity_id(*itr)) ThrowException();

  EntityId entity_id = *itr;
  bool has_set_one_synonym = false;
  itr++;
  while (itr != tokens.end() && *itr != ";") {
    if (!PQL::is_ident(*itr)) ThrowException();

    query->set_synonym(*itr, entity_id);
    has_set_one_synonym = true;
    itr++;
    if (itr != tokens.end() && *itr == ",") {
      itr++;  // read in next synonym
    }
  }

  if (!has_set_one_synonym) ThrowException();
  if (itr == tokens.end()) ThrowException();
  itr++;
  return query;
}

// synonym (',' synonym)*
std::unique_ptr<Query> SynonymParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    std::unique_ptr<Query> query) {
  // TODO(JL): Support multiple synonyms selection after
  // requirement is introduced
  if (itr == tokens.end() || *itr != "Select" && *itr != ",") ThrowException();
  itr++;
  if (!PQL::is_ident(*itr)) ThrowException();
  query->add_selected_synonym(*itr);
  itr++;
  return query;
}

// 'such' 'that' relRef
// e.g. relRef = Modifies(6, v)
std::unique_ptr<Query> SuchThatParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    std::unique_ptr<Query> query) {
  if (itr == tokens.end()) ThrowException();
  if (*itr++ != "such") ThrowException();
  if (*itr++ != "that") ThrowException();

  std::string rel_ident = *itr++;
  if (*itr++ != "(") ThrowException();
  ArgumentPtr arg1 = query->CreateArgument(*itr++);
  if (*itr++ != ",") ThrowException();
  ArgumentPtr arg2 = query->CreateArgument(*itr++);
  if (*itr != ")") ThrowException();

  query->add_clause(PQL::get_rel_ref(
      rel_ident, std::move(arg1), std::move(arg2)));

  itr++;
  return query;
}

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
std::unique_ptr<Query> PatternParseState::parse(
    const std::vector<std::string> &tokens,
    parse_position &itr,
    std::unique_ptr<Query> query) {
  if (itr == tokens.end()) ThrowException();
  if (*itr++ != "pattern") ThrowException();
  // TODO(jl): replace with check that it is syn-assign
  if (!PQL::is_ident(*itr++)) ThrowException();
  if (*itr++ != "(") ThrowException();
  ArgumentPtr arg1 = query->CreateArgument(*itr++);
  if (*itr++ != ",") ThrowException();
  ArgumentPtr arg2 = query->CreateArgument(*itr++);
  if (*itr != ")") ThrowException();

  query->add_clause(PQL::get_rel_ref(
      "pattern", std::move(arg1), std::move(arg2)));
  itr++;
  return query;
}

ParseState::~ParseState() = default;
}  // namespace qps
