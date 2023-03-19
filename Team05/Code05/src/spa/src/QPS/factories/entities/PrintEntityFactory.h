#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class PrintEntityFactory : public IntEntityFactory {
public:
  PrintEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
      return CreateInstanceList(pkb->get_print());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
      return Entity(pkb->get_var_name_from_line(index.get_int()));
  }
};
}  // namespace qps
