#include "SynonymArg.h"

#include "QPS/evaluator/TableJoiner.h"

namespace qps {
void SynonymArg::InitializeEntities(
    Table &table, pkb::PKBReadPtr &pkb, EntitySet &results) {
  if (table.HasColumn(syn_name_)) {
    std::vector<std::vector<Entity>> values;
    table.Select({syn_name_}, values);
    for (auto &entities : values) {
      results.insert(entities.at(0));
    }
  } else {
    results = master_entity_factory_.GetAllFromPKB(
        entity_type_, pkb);
  }
}
}  // namespace qps
