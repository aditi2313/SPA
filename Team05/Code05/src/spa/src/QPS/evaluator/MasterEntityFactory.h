#include "EntityFactory.h"
#include "QPS/models/PQL.h"

namespace qps {

class MasterEntityFactory {
 public:
  MasterEntityFactory() {
    entity_factories_.insert({PQL::kVariableEntityId, std::make_unique<VariableEntityFactory>()});
  }

  inline bool is_entity_id(EntityId entity_id) {
    return entity_factories_.find(entity_id) != entity_factories_.end();
  }

  EntityPtr CreateInstance(EntityId entity_id, int number) {
    return entity_factories_.at(entity_id)->CreateInstance(number);
  }

  EntityPtrList GetAllFromPKB(EntityId entity_id, PKBPtr &pkb) {
    return entity_factories_.at(entity_id)->GetAllFromPKB(std::move(pkb));
  }

 private:

  std::unordered_map<std::string, EntityFactoryPtr> entity_factories_;
};
}


