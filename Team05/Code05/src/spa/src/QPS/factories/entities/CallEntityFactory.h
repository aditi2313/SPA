#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "IntEntityFactory.h"

namespace qps {

class CallEntityFactory : public IntEntityFactory {
public:
  CallEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
      return CreateInstanceList(pkb->get_calls());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
      return Entity(pkb->get_proc_name_from_line(index.get_int()));
  }
};
}  // namespace qps
