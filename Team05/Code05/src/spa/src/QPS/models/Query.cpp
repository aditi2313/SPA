#include "Query.h"

namespace qps {
ArgumentPtr Query::CreateArgument(std::string token) {
  if (PQL::is_ident_arg(token)) {
    token = token.substr(1, token.size() - 2);
    return std::make_unique<IdentArg>(token);
  }

  if (PQL::is_wildcard(token)) {
    return std::make_unique<Wildcard>();
  }

  if (PQL::is_integer(token)) {
    return std::make_unique<IntegerArg>(stoi(token));
  }

  // Expression Arg
  if (PQL::is_pattern_exact(token)) {
    token = token.substr(1, token.size() - 2);
    return std::make_unique<ExpressionArg>(token, true);
  }

  if (PQL::is_pattern_wildcard(token)) {
    // Remove first and last wildcard characters
    token = token.substr(2, token.size() - 4);
    return std::make_unique<ExpressionArg>(token, false);
  }

  auto syn_arg = std::make_unique<SynonymArg>(token);
  if (is_declared_synonym_name(token)) {
    syn_arg->set_entity_name(get_synonym(token)->get_entity_name());
  }
  return syn_arg;
}
}  // namespace qps
