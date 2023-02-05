#pragma once

#include "Entity.h"

namespace models {

// An entity identified by an IDENT
// e.g. Procedure / Variable
class IdentEntity : public Entity {
 public:
  explicit IdentEntity(std::string ident) : Entity(), ident_(ident) {}

  bool operator<(const IdentEntity &other) {
    return ident_ < other.ident_;
  }

  bool operator==(const IdentEntity &other) {
    return ident_ == other.ident_;
  }

  operator std::string() { return ident_; }

 private:
  std::string ident_;
};

class Procedure : public IdentEntity {
 public:
  Procedure(std::string ident) : IdentEntity(ident) {}
};

class Variable : public IdentEntity {
 public:
  Variable(std::string ident) : IdentEntity(ident) {}
};
}
