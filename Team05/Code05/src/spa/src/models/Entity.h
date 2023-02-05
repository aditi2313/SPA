#pragma once

#include <string>

namespace models {
// Stub for a design entity
// Can be: procedure / stmt / variable / constant
class Entity {
 public:
  Entity() {}
  explicit Entity(std::string ident) : ident_(ident) {}

  // TODO(JL): be replaced with real value in real Entity class
  operator std::string() const { return ident_; }
  virtual ~Entity() {}

  friend bool operator<(const Entity &LHS, const Entity &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
  friend bool operator==(const Entity &LHS, const Entity &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
 private:
  std::string ident_;
};
}  // namespace models
