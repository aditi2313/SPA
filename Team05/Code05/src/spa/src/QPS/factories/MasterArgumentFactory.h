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
  inline std::unique_ptr<SynonymArg> CreateSynonym(std::string token) {
    return std::make_unique<SynonymArg>(token);
  }

  // synonym | _ | INTEGER | "ident"
  inline ArgumentPtr CreateEntOrStmtRef(std::string token) {
    if (PQL::is_wildcard(token)) {
      return CreateWildcard();
    }

    if (PQL::is_ident_arg(token)) {
      return CreateIdentArg(token);
    }

    if (PQL::is_integer(token)) {
      return CreateIntegerArg(token);
    }

    assert(PQL::is_synonym(token));
    return CreateSynonym(token);
  }

  // "ident" | INTEGER | attrRef
  // attrRef: synonym.attrName
  inline ArgumentPtr CreateRef(std::string token) {
    if (PQL::is_ident_arg(token)) {
      return CreateIdentArg(token);
    }

    if (PQL::is_integer(token)) {
      return CreateIntegerArg(token);
    }

    assert(PQL::is_attr_ref(token));
    return CreateAttrRef(token);
  }

  inline std::unique_ptr<Argument> CreateExpressionSpec(std::string token) {
    if (PQL::is_wildcard(token)) {
      return CreateWildcard();
    }

    if (PQL::is_pattern_wildcard(token)) {
      return CreateWildcardExpression(token);
    }

    assert(PQL::is_pattern_exact(token));
    return CreateExactExpression(token);
  }

  inline std::unique_ptr<ExpressionArg> CreateWildcardExpression(
      std::string token) {
    token = token.substr(2, token.size() - 4);

    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(
          std::move(AST), false);
    } catch (std::exception _) {
      throw PqlSyntaxErrorException("Invalid expression");
    }
  }

  inline std::unique_ptr<ExpressionArg> CreateExactExpression(
      std::string token) {
    token = token.substr(1, token.size()- 2);

    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(
          std::move(AST), true);
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


  // AttrRef: e.g. s.stmt#, v.varName, p.procName, constant.value
  inline std::unique_ptr<SynonymArg> CreateAttrRef(std::string token) {
    auto [syn_name, attr_name] = PQL::split_attr_ref(token);
    auto syn_arg = std::make_unique<SynonymArg>(syn_name);
    syn_arg->set_attr_name(attr_name);
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

    assert(PQL::is_synonym(token));
    return CreateSynonym(token);
  }

  // synonym | _ | INTEGER
  inline ArgumentPtr CreateStmtRef(std::string token) {
    if (PQL::is_wildcard(token)) {
      return CreateWildcard();
    }

    if (PQL::is_integer(token)) {
      return CreateIntegerArg(token);
    }

    assert(PQL::is_synonym(token));
    return CreateSynonym(token);
  }
};
}  // namespace qps


