#include <memory>
#include <string>
#include <unordered_map>

#include "EntityFactory.h"
#include "QPS/models/PQL.h"

namespace qps {

class MasterEntityFactory {
 public:
  MasterEntityFactory() {
    entity_factories_.insert(
        {PQL::kProcedureEntityId, std::make_unique<ProcedureEntityFactory>()});
    entity_factories_.insert(
        {PQL::kStmtEntityId, std::make_unique<StmtEntityFactory>()});
    entity_factories_.insert(
        {PQL::kReadEntityId, std::make_unique<ReadEntityFactory>()});
    entity_factories_.insert(
        {PQL::kPrintEntityId, std::make_unique<PrintEntityFactory>()});
    entity_factories_.insert(
        {PQL::kAssignEntityId, std::make_unique<AssignEntityFactory>()});
    entity_factories_.insert(
        {PQL::kCallEntityId, std::make_unique<CallEntityFactory>()});
    entity_factories_.insert(
        {PQL::kWhileEntityId, std::make_unique<WhileEntityFactory>()});
    entity_factories_.insert(
        {PQL::kIfEntityId, std::make_unique<IfEntityFactory>()});
    entity_factories_.insert(
        {PQL::kVariableEntityId, std::make_unique<VariableEntityFactory>()});
    entity_factories_.insert(
        {PQL::kConstantEntityId, std::make_unique<ConstantEntityFactory>()});
  }

  inline bool is_entity_id(EntityId entity_id) {
    return entity_factories_.find(entity_id) != entity_factories_.end();
  }

  inline EntityPtr CreateInstance(EntityId entity_id, int number) {
    return entity_factories_.at(entity_id)->CreateInstance(number);
  }

  inline EntityPtr CreateInstance(EntityId entity_id, Ident ident) {
    return entity_factories_.at(entity_id)->CreateInstance(ident);
  }

  inline EntityPtrList GetAllFromPKB(EntityId entity_id, PKBPtr &pkb) {
    return entity_factories_.at(entity_id)->GetAllFromPKB(pkb);
  }

 private:
  std::unordered_map<std::string, EntityFactoryPtr> entity_factories_;
};
}  // namespace qps


