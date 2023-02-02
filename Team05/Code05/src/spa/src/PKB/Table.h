#pragma once
#include <iostream>
#include <vector>

namespace pkb {

template <class T>
class Table {
 public:
  std::vector<T> rows_;
  inline void add_row(T row) {
      rows_.push_back(row);
  }
  inline T get_row(int num) {
      return rows_.at(num);
  }
};
}  // namespace pkb
