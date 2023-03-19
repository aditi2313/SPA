#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class VariableEntityFactory : public IdentEntityFactory {
public:
  VariableEntityFactory() : IdentEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
      return CreateInstanceList(pkb->get_variables());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
      throw QpsEvaluatorException(
          "Variable does not have a secondary attr value");
  }
};

}  // namespace qps
