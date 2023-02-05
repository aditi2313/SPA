#pragma once

#include <string>

namespace models {
// Stub for a design entity
// Can be: procedure / stmt / variable / constant
class EntityStub {
 public:
  EntityStub() {}
  explicit EntityStub(std::string ident) : ident_(ident) {}

  // TODO(JL): be replaced with real value in real Entity class
  operator std::string() const { return ident_; }
  virtual ~EntityStub() {}

  friend bool operator<(const EntityStub &LHS, const EntityStub &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
  friend bool operator==(const EntityStub &LHS, const EntityStub &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
 private:
  std::string ident_;
};
}  // namespace models
