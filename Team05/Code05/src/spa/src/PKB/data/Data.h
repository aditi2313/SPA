#pragma once

#include <cassert>
#include <unordered_set>

namespace pkb {
template <class T, class SecondIndexes = Key>
class Data {
 public:
  explicit Data(T line) : line_(line) {}

  inline T get_index() { return line_; }

  inline std::unordered_set<SecondIndexes>& get_second_indexes() {
    return second_indexes_;
  }

 protected:
  T line_;
  std::unordered_set<SecondIndexes> second_indexes_;
};

}  // namespace pkb
