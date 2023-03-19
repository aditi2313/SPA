#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/models/arguments/Export.h"
#include "QPS/models/Query.h"
#include "QPS/factories/arguments/Export.h"

namespace qps {
class MasterArgumentFactory {
 public:
  MasterArgumentFactory() {
    argument_factories_.insert(
        {ArgumentType::kAttrRef, std::make_unique<AttrRefFactory>()});
    argument_factories_.insert(
        {ArgumentType::kExactExprArg,
         std::make_unique<ExactExpressionArgFactory>()});
    argument_factories_.insert(
        {ArgumentType::kWildcardExprArg,
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
    assert(CheckSyntax(argument_type, token));
    return argument_factories_.at(argument_type)->Create(token);
  }

  inline bool CheckSyntax(ArgumentType argument_type, std::string token) {
    return argument_factories_.at(argument_type)->CheckSyntax(token);
  }

  inline ArgumentPtr Create(
      std::vector<ArgumentType> possible_arg_types,
      std::string token) {
    for (auto &arg_type : possible_arg_types) {
      if (CheckSyntax(arg_type, token)) {
        return Create(arg_type, token);
      }
    }

    throw PqlSyntaxErrorException(
        "Argument token does not fit any possible argument types");
  }

 private:
  std::unordered_map<ArgumentType, ArgumentFactoryPtr> argument_factories_;
};
}  // namespace qps


