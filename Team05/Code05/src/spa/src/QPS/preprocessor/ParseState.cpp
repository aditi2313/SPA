#include "ParseState.h"
#include "Parser.h"
#include "common/Exceptions.h"
#include "models/EntityStub.h"

namespace qps {
// design-entity synonym (',' synonym)* ';'
ParseState::parse_position DeclarationParseState::parse(std::vector<std::string> &tokens,
                                                        parse_position itr,
                                                        Query &query) {
  if (!Parser::is_design_entity(*itr))
    throw PqlSyntaxErrorException("Invalid design entity in declaration");

  models::EntityStub design_entity = Parser::get_design_entity(*itr);
  bool has_set_one_synonym = false;
  itr++;
  while (itr != tokens.end() && *itr != ";") {
    if (!Parser::is_ident(*itr))
      throw PqlSyntaxErrorException("Invalid identifier in declaration");

    query.set_synonym(*itr, design_entity);
    has_set_one_synonym = true;
    itr++;
    if (itr != tokens.end() && *itr == ",") {
      itr++; // read in next synonym
    }
  }

  if (!has_set_one_synonym) throw PqlSyntaxErrorException("Invalid declaration syntax");
  if (itr == tokens.end()) throw PqlSyntaxErrorException("Missing semi-colon in declaration");
  return ++itr;
}

ParseState::parse_position SynonymParseState::parse(std::vector<std::string> &tokens,
                                                    parse_position itr,
                                                    Query &query) {
  // TODO(JL): Support multiple synonyms selection after
  // requirement is introduced
  if (Parser::is_ident(*itr)) throw PqlSyntaxErrorException("Invalid synonym identifier");
  query.add_selected_synonym(*itr);
  return ++itr;
}

ParseState::~ParseState() = default;
}  // namespace qps