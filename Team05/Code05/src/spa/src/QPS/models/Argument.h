#pragma once

#include <string>

namespace qps {
// An argument for a clause.
// e.g. Clause(Argument, Argument)
// It can be a synonym for statement, procedure, variable,
// character strings, wildcard, or expressions for exact/partial matches
// TODO(JL): replace string with OOP and include wildcards etc.
class Argument {
 public:
  explicit Argument(std::string arg) : arg(arg) {}
  bool operator==(const Argument &other) const {
    return arg == other.arg;
  }
 private:
  std::string arg;
};
}  // namespace qps
