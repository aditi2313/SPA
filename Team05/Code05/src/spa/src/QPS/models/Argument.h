#pragma once

#include <string>
#include "models/models.h"

namespace qps {
// An argument for a clause.
// e.g. Clause(Argument, Argument)
// It can be a synonym for statement, procedure, variable,
// character strings, wildcard, or expressions for exact/partial matches
// TODO(JL): replace string with OOP and include wildcards etc.
class Argument {
 public:
  explicit Argument(std::string arg) : arg(arg) {}
  inline bool operator==(const Argument &other) const {
    return arg == other.arg;
  }

  std::string get_arg() {
    return arg;
  }
 private:
  std::string arg;
};

// synonym | '_' | INTEGER
class StmtRef : public Argument {
 public:
  models::stmt stmt_;
};

// synonym | '_' | "IDENT"
class EntRef : public Argument {

};

}  // namespace qps
