#pragma once

#include <string>

namespace models {
// Stub for a design entity
// Can be: procedure / stmt / variable / constant
class EntityStub {
 public:
  // TODO(JL): be replaced with real value in real Entity class
  operator std::string() const { return "abc"; }

  friend bool operator<(const EntityStub &LHS, const EntityStub &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
  friend bool operator==(const EntityStub &LHS, const EntityStub &RHS) {
    // TODO(JL): be replaced with real comparison in real Entity class
    return true;
  }
};
}  // namespace models

