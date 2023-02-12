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
        {PQL::kProcedureEntityName,
         std::make_unique<ProcedureEntityFactory>()});
    entity_factories_.insert(
        {PQL::kStmtEntityName, std::make_unique<StmtEntityFactory>()});
    entity_factories_.insert(
        {PQL::kReadEntityName, std::make_unique<ReadEntityFactory>()});
    entity_factories_.insert(
        {PQL::kPrintEntityName, std::make_unique<PrintEntityFactory>()});
    entity_factories_.insert(
        {PQL::kAssignEntityName, std::make_unique<AssignEntityFactory>()});
    entity_factories_.insert(
        {PQL::kCallEntityName, std::make_unique<CallEntityFactory>()});
    entity_factories_.insert(
        {PQL::kWhileEntityName, std::make_unique<WhileEntityFactory>()});
    entity_factories_.insert(
        {PQL::kIfEntityName, std::make_unique<IfEntityFactory>()});
    entity_factories_.insert(
        {PQL::kVariableEntityName, std::make_unique<VariableEntityFactory>()});
    entity_factories_.insert(
        {PQL::kConstantEntityName, std::make_unique<ConstantEntityFactory>()});
  }

  inline bool is_entity_name(EntityName entity_name) {
    return entity_factories_.find(entity_name) != entity_factories_.end();
  }

  inline EntityPtr CreateInstance(EntityName entity_name, int number) {
    return entity_factories_.at(entity_name)->CreateInstance(number);
  }

  inline EntityPtr CreateInstance(EntityName entity_name, Ident ident) {
    return entity_factories_.at(entity_name)->CreateInstance(ident);
  }

  inline EntityPtrList GetAllFromPKB(EntityName entity_name, PKBPtr &pkb) {
    return entity_factories_.at(entity_name)->GetAllFromPKB(pkb);
  }

 private:
  std::unordered_map<std::string, EntityFactoryPtr> entity_factories_;
};
}  // namespace qps


