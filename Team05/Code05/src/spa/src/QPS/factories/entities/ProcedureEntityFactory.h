#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class ProcedureEntityFactory : public IdentEntityFactory {
 public:
  ProcedureEntityFactory() : IdentEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_procedures());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Procedure does not have a secondary attr value");
  }
};

}  // namespace qps
