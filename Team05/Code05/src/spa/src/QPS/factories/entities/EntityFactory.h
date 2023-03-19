#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "PKB/PKBRead.h"
#include "common/exceptions/QPSExceptions.h"

using namespace models;  // NOLINT

namespace qps {
class EntityFactory {
 public:
  EntityFactory() {}
  virtual EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) = 0;
  virtual Entity GetAttrValue(const Entity &index,
                              const pkb::PKBReadPtr &pkb) = 0;

  virtual bool is_integer() { return false; }
  virtual bool is_ident() { return false; }

  virtual ~EntityFactory() = default;
};

using EntityFactoryPtr = std::unique_ptr<EntityFactory>;
}  // namespace qps
