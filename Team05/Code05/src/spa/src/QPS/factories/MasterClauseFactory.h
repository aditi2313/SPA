#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "ClauseFactory.h"
#include "QPS/models/PQL.h"

namespace qps {
class MasterClauseFactory {
 public:
  MasterClauseFactory() {
    clause_factories_.insert(
        {PQL::kModifiesRelName, std::make_unique<ModifiesFactory>()});
    clause_factories_.insert(
        {PQL::kFollowsRelName, std::make_unique<FollowsFactory>()});
    clause_factories_.insert(
        {PQL::kFollowsTRelName, std::make_unique<FollowsTFactory>()});
    clause_factories_.insert(
        {PQL::kParentRelName, std::make_unique<ParentFactory>()});
    clause_factories_.insert(
        {PQL::kParentTRelName, std::make_unique<ParentTFactory>()});
    clause_factories_.insert(
        {PQL::kUsesRelName, std::make_unique<UsesFactory>()});
    clause_factories_.insert(
        {PQL::kPatternRelName, std::make_unique<PatternFactory>()});
    clause_factories_.insert(
        {PQL::kCallsRelName, std::make_unique<CallsFactory>()});
    clause_factories_.insert(
        {PQL::kCallsTRelName, std::make_unique<CallsTFactory>()});
  }

  inline ClausePtr Create(
      PQL::RelName rel_name,
      ArgumentPtr arg1,
      ArgumentPtr arg2) {
    return clause_factories_.at(rel_name)->Create(
        std::move(arg1), std::move(arg2));
  }

  inline bool Validate(
      PQL::RelName rel_name,
      ArgumentPtr &arg1,
      ArgumentPtr &arg2) {
    return clause_factories_.at(rel_name)->Validate(arg1, arg2);
  }

 private:
  std::unordered_map<std::string, ClauseFactoryPtr> clause_factories_;
};
}  // namespace qps


