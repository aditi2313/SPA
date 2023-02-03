#include "ParseState.h"
#include "Parser.h"
#include "common/Exceptions.h"
#include "models/EntityStub.h"

namespace qps {
// design-entity synonym (',' synonym)* ';'
ParseState::parse_position DeclarationParseState::parse(std::vector<std::string> &tokens,
                                                        parse_position itr,
                                                        Query &query) {
  if (!Parser::is_design_entity(*itr)) ThrowException();

  models::EntityStub design_entity = Parser::get_design_entity(*itr);
  bool has_set_one_synonym = false;
  itr++;
  while (itr != tokens.end() && *itr != ";") {
    if (!Parser::is_ident(*itr)) ThrowException();

    query.set_synonym(*itr, design_entity);
    has_set_one_synonym = true;
    itr++;
    if (itr != tokens.end() && *itr == ",") {
      itr++; // read in next synonym
    }
  }

  if (!has_set_one_synonym) ThrowException();
  if (itr == tokens.end()) ThrowException();
  return ++itr;
}

ParseState::parse_position SynonymParseState::parse(std::vector<std::string> &tokens,
                                                    parse_position itr,
                                                    Query &query) {
  // TODO(JL): Support multiple synonyms selection after
  // requirement is introduced
  itr++; // Read tokens after 'select'
  if (Parser::is_ident(*itr)) ThrowException();
  query.add_selected_synonym(*itr);
  return ++itr;
}

// 'such' 'that' relRef
// e.g. relRef = Modifies(6, v)
ParseState::parse_position SuchThatParseState::parse(std::vector<std::string> &tokens,
                                                     parse_position itr,
                                                     Query &query) {
  if (*itr++ != "such") ThrowException();
  if (*itr++ != "that") ThrowException();

  std::string rel_ident = *itr++;
  if (*itr++ != "(") ThrowException();
  std::string arg1 = *itr++;
  if (*itr++ != ",") ThrowException();
  std::string arg2 = *itr++;
  if (*itr != ")") ThrowException();

  query.add_clause(Parser::get_rel_ref(rel_ident, arg1, arg2));

  return ++itr;
}

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
ParseState::parse_position PatternParseState::parse(std::vector<std::string> &tokens,
                                                    parse_position itr,
                                                    Query &query) {
  if (*itr++ != "pattern") ThrowException();
  // TODO(jl): replace with check that it is syn-assign
  itr++;
//  if (Parser::is_ident(*itr++)) ThrowException();
  if (*itr++ != "(") ThrowException();
  std::string arg1 = *itr++;
  if (*itr++ != ",") ThrowException();
  std::string arg2 = *itr++;
  if (*itr != ")") ThrowException();

  query.add_clause(Parser::get_rel_ref("pattern", arg1, arg2));
  return ++itr;
}

ParseState::~ParseState() = default;
}  // namespace qps