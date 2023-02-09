#pragma once

#include <string>

#include "Entity.h"

namespace models {
// An entity identified by an INTEGER
// e.g. Stmt / Constant
class IntEntity : public Entity {
 public:
  explicit IntEntity(int number) : Entity(), number_(number) {}

  bool operator<(const IntEntity &other) {
    return number_ < other.number_;
  }

  bool operator==(const IntEntity &other) {
    return number_ == other.number_;
  }

  operator std::string() { return std::to_string(number_); }

 private:
  int number_;
};

class Constant : public IntEntity {
 public:
  explicit Constant(int number) : IntEntity(number) {}
};
}  // namespace models
