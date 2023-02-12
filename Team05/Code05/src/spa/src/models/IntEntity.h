#pragma once

#include <string>
#include <memory>

#include "Entity.h"

namespace models {
// An entity identified by an INTEGER
// e.g. Stmt / Constant
class IntEntity : public Entity {
 public:
  explicit IntEntity(int number) : Entity(), number_(number) {}

  inline bool operator<(Entity &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    return number_ <
        (reinterpret_cast<IntEntity *>(&other))->number_;
  }

  inline bool operator==(Entity &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    return number_ ==
        (reinterpret_cast<IntEntity *>(&other))->number_;
  }

  inline EntityPtr Copy() override {
    return std::make_unique<IntEntity>(*this);
  }

  operator std::string() override {
    return std::to_string(number_);
  }

 private:
  int number_;
};

class Constant : public IntEntity {
 public:
  explicit Constant(int number) : IntEntity(number) {}
};
}  // namespace models