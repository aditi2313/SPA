#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "IntEntityFactory.h"

namespace qps {

class AssignEntityFactory : public IntEntityFactory {
 public:
  AssignEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_assign());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException("Assign does not have a secondary attr value");
  }
};
}  // namespace qps
