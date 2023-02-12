#pragma once

#include <string>
#include <memory>

#include "Entity.h"

namespace models {
// An entity identified by an IDENT
// e.g. Procedure / Variable
class IdentEntity : public Entity {
 public:
  explicit IdentEntity(std::string ident) : Entity(), ident_(ident) {}

  inline bool operator<(Entity &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    return ident_ <
        (reinterpret_cast<IdentEntity *>(&other))->ident_;
  }

  inline bool operator==(Entity &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    return ident_ ==
        (reinterpret_cast<IdentEntity *>(&other))->ident_;
  }

  inline bool operator!=(Entity &other) override {
    return !(*this == other);
  }

  operator std::string() override { return ident_; }
  virtual ~IdentEntity() = 0;

 private:
  std::string ident_;
};

class Procedure : public IdentEntity {
 public:
  explicit Procedure(std::string ident) : IdentEntity(ident) {}

  inline EntityPtr Copy() override {
    return std::make_unique<Procedure>(*this);
  }
};

class Variable : public IdentEntity {
 public:
  explicit Variable(std::string ident) : IdentEntity(ident) {}

  inline EntityPtr Copy() override {
    return std::make_unique<Variable>(*this);
  }
};
}  // namespace models
