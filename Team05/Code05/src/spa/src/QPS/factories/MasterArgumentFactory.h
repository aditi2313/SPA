#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/models/arguments/Export.h"
#include "QPS/models/Query.h"

namespace qps {
class MasterArgumentFactory {
 public:
  inline std::unique_ptr<ExpressionArg> CreateExpressionArg(std::string token) {
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

  inline std::unique_ptr<IdentArg> CreateIdentArg(std::string token) {
    // Remove first and last quotation marks
    token = token.substr(1, token.size() - 2);
    return std::make_unique<IdentArg>(token);
  }

  inline std::unique_ptr<IntegerArg> CreateIntegerArg(std::string token) {
    return std::make_unique<IntegerArg>(stoi(token));
  }

  inline std::unique_ptr<SynonymArg> CreateSynonym(std::string token) {
    std::string syn_name = token;
    std::string attr_name;
    // AttrRef: e.g. s.stmt#, v.varName, p.procName, constant.value
    if (PQL::is_attr_ref(token)) {
      std::tie(syn_name, attr_name) = PQL::split_attr_ref(token);
    }

    auto syn_arg = std::make_unique<SynonymArg>(syn_name);
    if (!attr_name.empty()) {
      syn_arg->set_attr_name(attr_name);
    }
    return syn_arg;
  }

  inline std::unique_ptr<Wildcard> CreateWildcard() {
    return std::make_unique<Wildcard>();
  }

  // synonym | _ | "ident"
  inline ArgumentPtr CreateEntRef(std::string token) {
    if (PQL::is_wildcard(token)) {
      return CreateWildcard();
    }

    if (PQL::is_ident_arg(token)) {
      return CreateIdentArg(token);
    }

    return CreateSynonym(token);
  }

  // synonym | _ | INTEGER
  inline ArgumentPtr CreateStmtRef(std::string token) {
    if (PQL::is_wildcard(token)) {
      return CreateWildcard();
    }

    if (PQL::is_integer(token)) {
      return CreateIdentArg(token);
    }

    return CreateSynonym(token);
  }
};
}  // namespace qps


