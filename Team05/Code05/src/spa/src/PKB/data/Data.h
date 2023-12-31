#pragma once

#include <cassert>
#include <unordered_set>
#include <variant>
#include <string>

#include "Types.h"
#include "DataWrapper.h"

namespace pkb {
// todo: set this definition elsewhere
template <class T, class SecondIndexes = Key>
class Data : public DataWrapper {
 public:
  explicit Data(T line) : line_(line) {}

  inline T get_index() const { return line_; }

  inline const std::unordered_set<SecondIndexes>& get_second_indexes() const {
    return second_indexes_;
  }

    inline Key get_key() override {
        return line_;
    }

 protected:
  T line_;
  std::unordered_set<SecondIndexes> second_indexes_;
};

}  // namespace pkb
