#pragma once
#include <iostream>
#include <vector>

namespace pkb {

template <class T>
class Table {
 public:
  std::vector<T> rows;
  void add_row(T row);
  T get_row(int num);
};
}  // namespace pkb
