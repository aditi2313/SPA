#include "Query.h"
#include "SP/SourceProcessor.h"

namespace qps {
ArgumentPtr Query::CreateArgument(std::string token) {
  if (PQL::is_ident_arg(token)) {
    // Remove first and last quotation marks
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
  if (PQL::is_pattern_exact(token) || PQL::is_pattern_wildcard(token)) {
    bool is_exact = PQL::is_pattern_exact(token);
    // Remove first and last quotation marks
    // or first and last wildcard + quotation marks
    token = is_exact
            ? token.substr(1, token.size() - 2)
            : token.substr(2, token.size() - 4);

    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(
          std::move(AST), is_exact);
    } catch (std::exception _) {
      throw PqlSyntaxErrorException("Invalid expression");
    }
  }

  std::string syn_name = token;
  std::string attr_name;
  // AttrRef: e.g. s.stmt#, v.varName, p.procName, constant.value
  if (PQL::is_attr_ref(token)) {
    std::tie(syn_name, attr_name) = PQL::split_attr_ref(token);
  }

  auto syn_arg = std::make_unique<SynonymArg>(syn_name);
  if (is_synonym_name_declared(syn_name)) {
    syn_arg->set_entity_name(get_declared_synonym_entity_name(syn_name));
  }
  if (!attr_name.empty()) {
    syn_arg->set_attr_name(attr_name);
  }
  return syn_arg;
}
}  // namespace qps
