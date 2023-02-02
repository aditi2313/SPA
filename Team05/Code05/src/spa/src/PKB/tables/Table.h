#pragma once

#include <unordered_map>
#include <utility>
#include <unordered_set>

namespace pkb {

template <class T>
class Table {
 public:
  Table() {}
  virtual ~Table() {}
  inline void add_row(int id, T row) {
    table_.insert(std::make_pair(id, row));
    rows_.insert(id);
  }
  inline T get_row(int num) { return table_.at(num); }
  inline std::unordered_set<int> get_rows() { return rows_; }

  friend bool operator==(const Table<T>& LHS, const Table<T>& RHS) {
    return LHS.rows_ == RHS.rows_ && LHS.table_ == RHS.table_;
  }

 private:
  std::unordered_set<int> rows_;
  std::unordered_map<int, T> table_;
};
}  // namespace pkb
