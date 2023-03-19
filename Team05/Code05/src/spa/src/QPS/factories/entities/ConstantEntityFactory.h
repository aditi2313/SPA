#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class ConstantEntityFactory : public IntEntityFactory {
 public:
  ConstantEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_constants());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Constant does not have a secondary attr value");
  }
};

}  // namespace qps
