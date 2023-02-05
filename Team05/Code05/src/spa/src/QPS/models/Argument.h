#pragma once
#include <string>
#include <sstream>

namespace qps {
// An argument for a clause.
// e.g. Clause(Argument, Argument)
// It can be a synonym for statement, procedure, variable,
// character strings, wildcard, or expressions for exact/partial matches
class Argument {
 public:
  explicit Argument(std::string arg) : arg(arg) {}
  inline bool operator==(const Argument &other) const {
    return arg == other.arg;
  }

  std::string to_string() {
    std::stringstream ss;
    ss << arg;
    return ss.str();
  }

    private:
       std::string arg;
};
}; //namespace qps
