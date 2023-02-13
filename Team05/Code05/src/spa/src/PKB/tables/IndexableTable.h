#pragma once

#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PKB/data/AssignData.h"
#include "PKB/data/ModifiesData.h"
#include "PKB/tables/IndexableTable.h"

namespace pkb {

/// <summary>
/// Class for table indexable by id.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class IndexableTable {
 public:
  IndexableTable() = default;

  inline void add_row(int line, T row) {
    id_map_[line] = rows_.size();
    rows_.push_back(std::move(row));
  }
  inline T get_row(int num) { return rows_.at(id_map_.at(num)); }

  inline std::set<int> get_indexes() {
    std::set<int> result;
    for (auto &[line, row] : id_map_) {
      result.insert(line);
    }
    return result;
  }

  bool exists(int line) { return id_map_.find(line) != id_map_.end(); }

  friend bool operator==(const IndexableTable<T> &LHS,
                         const IndexableTable<T> &RHS) {
    return LHS.rows_ == RHS.rows_;
  }

  std::unique_ptr<IndexableTable<T>> copy() {
    std::unique_ptr<IndexableTable<T>> result =
        std::make_unique<IndexableTable<T>>();
    result->rows_ = rows_;
    result->id_map_ = id_map_;
    return std::move(result);
  }

 protected:
  std::vector<T> rows_;
  std::unordered_map<int, int> id_map_;
};

typedef IndexableTable<ModifiesData> ModifiesTable;
typedef IndexableTable<AssignData> AssignTable;

template <typename T>
using IndexableTablePtr = std::unique_ptr<IndexableTable<T>>;
}  // namespace pkb
