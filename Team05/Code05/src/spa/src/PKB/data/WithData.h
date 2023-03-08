#pragma once

#include <string>
#include <unordered_set>
#include <cassert>

namespace pkb {
class WithData {
 public:
  explicit WithData(int line, std::string name)
    : line_(line), name_(name) {};

  friend bool operator==(const WithData &LHS, const WithData &RHS) {
    return LHS.line_ == RHS.line_ &&
        LHS.name_ == RHS.name_;
  }

  inline int get_index() { return line_; }

  inline std::string &get_name() { return name_; }

 private:
  int line_;
  std::string name_;
};
}  // namespace pkb
