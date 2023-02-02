#pragma once

#include <string>

namespace models {
// Stub for a design entity
// Can be: procedure / stmt / variable / constant
class Entity {
 public:
  // TODO(JL): be replaced with real value in real Entity class
  operator std::string() const { return "abc"; }
  virtual ~Entity() {}

  friend bool operator<(const Entity &LHS, const Entity &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
  friend bool operator==(const Entity &LHS, const Entity &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
};
}  // namespace models
