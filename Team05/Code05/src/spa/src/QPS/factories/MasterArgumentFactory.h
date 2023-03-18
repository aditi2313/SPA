#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/models/arguments/Export.h"
#include "QPS/models/Query.h"
#include "ArgumentFactory.h"

namespace qps {
class MasterArgumentFactory {
 public:
  MasterArgumentFactory() {
    argument_factories_.insert(
        {ArgumentType::kExactExpressionArg,
         std::make_unique<ExactExpressionArgFactory>()});
    argument_factories_.insert(
        {ArgumentType::kWildcardExpressionArg,
         std::make_unique<WildcardExpressionArgFactory>()});
    argument_factories_.insert(
        {ArgumentType::kIdentArg, std::make_unique<IdentArgFactory>()});
    argument_factories_.insert(
        {ArgumentType::kIntegerArg, std::make_unique<IntegerArgFactory>()});
    argument_factories_.insert(
        {ArgumentType::kSynonymArg, std::make_unique<SynonymArgFactory>()});
    argument_factories_.insert(
        {ArgumentType::kWildcard, std::make_unique<WildcardFactory>()});
  }

  inline ArgumentPtr Create(ArgumentType argument_type, std::string token) {
    return argument_factories_.at(argument_type)->Create(token);
  }

  inline bool CheckSyntax(ArgumentType argument_type, std::string token) {
    return argument_factories_.at(argument_type)->CheckSyntax(token);
  }

  inline ArgumentPtr Create(
      std::vector<ArgumentType> &possible_arg_types,
      std::string token) {
    for(auto &arg_type : possible_arg_types) {
      if (CheckSyntax(arg_type, token)) {
        return Create(arg_type, token);
      }
    }
    throw PqlSyntaxErrorException("Invalid argument syntax");
  }

  inline std::unique_ptr<SynonymArg> CreateSynonym(
      SynonymName syn_name, EntityType entity_type) {
    return std::make_unique<SynonymArg>(syn_name, entity_type);
  }

  // synonym | _ | INTEGER | "ident"
  inline ArgumentPtr CreateEntOrStmtRef(std::string token) {
    return Create();
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
    return Create(expression_spec_arg_types_, token);
  }


  // AttrRef: e.g. s.stmt#, v.varName, p.procName, constant.value
  inline std::unique_ptr<SynonymArg> CreateAttrRef(std::string token) {

  }

  // synonym | _ | "ident"
  inline ArgumentPtr CreateEntRef(std::string token) {
    return Create(ent_ref_arg_types_, token);
  }

 private:
  std::unordered_map<ArgumentType, ArgumentFactoryPtr> argument_factories_;
  std::vector<ArgumentType> ent_ref_arg_types_ {
    ArgumentType::kSynonymArg,
    ArgumentType::kWildcard,
    ArgumentType::kIntegerArg
  };
  std::vector<ArgumentType> stmt_ref_arg_types_ {
      ArgumentType::kSynonymArg,
      ArgumentType::kWildcard,
      ArgumentType::kIdentArg
  };
  std::vector<ArgumentType> expression_spec_arg_types_ {
      ArgumentType::kWildcard,
      ArgumentType::kWildcardExpressionArg,
      ArgumentType::kExactExpressionArg
  };

};
}  // namespace qps


