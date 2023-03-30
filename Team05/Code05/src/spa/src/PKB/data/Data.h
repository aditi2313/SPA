#pragma once

#include <cassert>
#include <unordered_set>
#include <variant>
#include <string>

#include "Types.h"

namespace pkb {
// todo: set this definition elsewhere
template <class T, class SecondIndexes = Index>
class Data {
 public:
  explicit Data(T line) : line_(line) {}

  inline T get_index() const { return line_; }

  inline const std::unordered_set<SecondIndexes>& get_second_indexes() const {
    return second_indexes_;
  }

 protected:
  T line_;
  std::unordered_set<SecondIndexes> second_indexes_;
};

}  // namespace pkb
