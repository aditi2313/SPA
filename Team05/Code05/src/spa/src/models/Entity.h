#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_set>

namespace models {

// Abstract base class for a design entity
// Represents a:
// Procedure | Stmt (Read | Print | Assign | Call | While | If)
// Variable | Constant
class Entity {
 public:
  Entity() {}
  virtual operator std::string() = 0;
  virtual ~Entity() = 0;
  virtual bool operator==(Entity &other) = 0;
  virtual bool operator!=(Entity &other) = 0;
  virtual bool operator<(Entity &other) = 0;
  virtual std::unique_ptr<Entity> Copy() = 0;
  virtual bool WeakEqual(Entity &other) = 0;
  virtual std::size_t hash() = 0;
};

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrList = std::vector<EntityPtr>;

auto const EntityPtrEqual =
    [](EntityPtr const &LHS, EntityPtr const &RHS) {
      return *LHS == *RHS;
    };

auto const EntityPtrHash = [](const EntityPtr &entity) {
  return entity->hash();
};

using EntityPtrHashset =
    std::unordered_set<EntityPtr,
                       decltype(EntityPtrHash),
                       decltype(EntityPtrEqual)>;
}  // namespace models
