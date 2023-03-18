#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "ClauseFactory.h"
#include "QPS/models/PQL.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class MasterClauseFactory {
 public:
  MasterClauseFactory() {
    clause_factories_.insert(
        {ClauseType::kAffects, std::make_unique<AffectsFactory>()});
    clause_factories_.insert(
        {ClauseType::kAffectsT, std::make_unique<AffectsTFactory>()});
    clause_factories_.insert(
        {ClauseType::kModifies, std::make_unique<ModifiesFactory>()});
    clause_factories_.insert(
        {ClauseType::kFollows, std::make_unique<FollowsFactory>()});
    clause_factories_.insert(
        {ClauseType::kFollowsT, std::make_unique<FollowsTFactory>()});
    clause_factories_.insert(
        {ClauseType::kParent, std::make_unique<ParentFactory>()});
    clause_factories_.insert(
        {ClauseType::kParentT, std::make_unique<ParentTFactory>()});
    clause_factories_.insert(
        {ClauseType::kUses, std::make_unique<UsesFactory>()});
    clause_factories_.insert(
        {ClauseType::kPatternAssign, std::make_unique<PatternAssignFactory>()});
    clause_factories_.insert(
        {ClauseType::kPatternIf, std::make_unique<PatternIfFactory>()});
    clause_factories_.insert(
        {ClauseType::kPatternWhile, std::make_unique<PatternWhileFactory>()});
    clause_factories_.insert(
        {ClauseType::kCalls, std::make_unique<CallsFactory>()});
    clause_factories_.insert(
        {ClauseType::kCallsT, std::make_unique<CallsTFactory>()});
    clause_factories_.insert(
        {ClauseType::kNext, std::make_unique<NextFactory>()});
    clause_factories_.insert(
        {ClauseType::kNextT, std::make_unique<NextTFactory>()});
    clause_factories_.insert(
        {ClauseType::kWith, std::make_unique<WithFactory>()});
  }

  inline ClausePtr Create(
      ClauseType clause_type,
      ArgumentPtr arg1,
      ArgumentPtr arg2) {
    if (!clause_factories_.count(clause_type)) {
      throw PqlSyntaxErrorException("No such relation");
    }
    return clause_factories_.at(clause_type)->Create(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(
      ClauseType clause_type,
      ArgumentPtr &arg1,
      ArgumentPtr &arg2) {
    return clause_factories_.at(clause_type)->Validate(arg1, arg2);
  }

 private:
  std::unordered_map<ClauseType, ClauseFactoryPtr> clause_factories_;
};
}  // namespace qps
