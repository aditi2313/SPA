#pragma once

#include <string>

namespace models {
// Stub for a design entity
// Can be: procedure / stmt / variable / constant
class EntityStub {
 public:
  // TODO: be replaced with real value in real Entity class
  operator std::string() const { return "abc"; }
};
}  // namespace models

