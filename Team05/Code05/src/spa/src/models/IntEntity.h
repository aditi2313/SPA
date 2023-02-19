#pragma once

#include <string>
#include <memory>
#include <iostream>

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
        (dynamic_cast<IntEntity *>(&other))->number_;
  }

  inline bool operator==(Entity &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    return number_ ==
        (dynamic_cast<IntEntity *>(&other))->number_;
  }

  inline bool operator!=(Entity &other) override {
    return !(*this == other);
  }

  operator std::string() override {
    return std::to_string(number_);
  }

  inline int get_number() { return number_; }

  inline size_t hash() override {
    std::string str = typeid(*this).name()
        + std::to_string(number_);
    return std::hash<std::string>{}(str);
  }

 protected:
  int number_;
};

class Constant : public IntEntity {
 public:
  explicit Constant(int number) : IntEntity(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<Constant>(*this);
  }

  inline bool WeakEqual(Entity &other) override {
    return *this == other;
  }
};
}  // namespace models
