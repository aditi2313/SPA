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
  inline std::unique_ptr<SynonymArg> CreateSynonym(SynonymName syn_name) {
    return std::make_unique<SynonymArg>(syn_name);
  }

  inline std::unique_ptr<SynonymArg> CreateSynonym(
      SynonymName syn_name, EntityType entity_type) {
    return std::make_unique<SynonymArg>(syn_name, entity_type);
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

    throw PqlSyntaxErrorException(
        "Unexpected argument type in clause");
  }

  inline std::unique_ptr<ExpressionArg> CreateExpressionArg(
      std::string token, bool is_exact) {
    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(
          std::move(AST), is_exact);
    } catch (std::exception _) {
      throw PqlSyntaxErrorException("Invalid expression");
    }
  }

  inline std::unique_ptr<IdentArg> CreateIdentArg(std::string token) {
    if (!PQL::is_ident(token))
      throw PqlSyntaxErrorException("Invalid token for ident");
    return std::make_unique<IdentArg>(token);
  }

  inline std::unique_ptr<IntegerArg> CreateIntegerArg(std::string token) {
    if (!PQL::is_integer(token))
      throw PqlSyntaxErrorException("Invalid token for integer");
    return std::make_unique<IntegerArg>(stoi(token));
  }

  // AttrRef: e.g. s.stmt#, v.varName, p.procName, constant.value
  inline std::unique_ptr<SynonymArg> CreateAttrRef(
      SynonymName syn_name, AttrName attr_name) {
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

    if (PQL::is_synonym(token)) {
      return CreateSynonym(token);
    }

    throw PqlSyntaxErrorException(
        "Unexpected argument type in clause");
  }

  // synonym | _ | INTEGER
  inline ArgumentPtr CreateStmtRef(std::string token) {
    if (PQL::is_wildcard(token)) {
      return CreateWildcard();
    }

    if (PQL::is_integer(token)) {
      return CreateIntegerArg(token);
    }

    if (PQL::is_synonym(token)) {
      return CreateSynonym(token);
    }

    throw PqlSyntaxErrorException(
        "Unexpected argument type in clause");
  }
};
}  // namespace qps


