#include <iostream>
#include <vector>

#ifndef SPA_TABLE_H
#define SPA_TABLE_H

namespace pkb {

template <class T>
class Table {
 public:
  std::vector<T> rows;
  void add_row(T row);
  T get_row(int num);
};

#endif  // SPA_TABLE_H
}  // namespace pkb
