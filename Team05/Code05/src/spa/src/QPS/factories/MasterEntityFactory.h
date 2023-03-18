#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "EntityFactory.h"
#include "QPS/models/EntityType.h"
#include "QPS/models/PQL.h"

namespace qps {
class MasterEntityFactory {
 public:
  MasterEntityFactory() {
    entity_factories_.insert(
        {EntityType::kProcedure, std::make_unique<ProcedureEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kStmt, std::make_unique<StmtEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kRead, std::make_unique<ReadEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kPrint, std::make_unique<PrintEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kAssign, std::make_unique<AssignEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kCall, std::make_unique<CallEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kWhile, std::make_unique<WhileEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kIf, std::make_unique<IfEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kVariable, std::make_unique<VariableEntityFactory>()});
    entity_factories_.insert(
        {EntityType::kConstant, std::make_unique<ConstantEntityFactory>()});
  }

  inline EntitySet GetAllFromPKB(
      EntityType entity_type, const pkb::PKBReadPtr &pkb) {
    return entity_factories_.at(entity_type)->GetAllFromPKB(pkb);
  }

  inline Entity GetAttrValue(
      const EntityType entity_type,
      const Entity &index,
      const pkb::PKBReadPtr &pkb) {
    return entity_factories_.at(entity_type)->GetAttrValue(index, pkb);
  }

  inline bool is_integer(EntityType entity_type) {
    return entity_factories_.at(entity_type)->is_integer();
  }

  inline bool is_ident(EntityType entity_type) {
    return entity_factories_.at(entity_type)->is_ident();
  }

 private:
  std::unordered_map<EntityType, EntityFactoryPtr> entity_factories_;
};
}  // namespace qps


