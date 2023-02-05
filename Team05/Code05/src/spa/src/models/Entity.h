#pragma once

#include <string>

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
};

using EntityPtr = std::unique_ptr<Entity>;
}  // namespace models
