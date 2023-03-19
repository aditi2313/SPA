#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class WhileEntityFactory : public IntEntityFactory {
 public:
  WhileEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_whiles());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException("While does not have a secondary attr value");
  }
};
}  // namespace qps
