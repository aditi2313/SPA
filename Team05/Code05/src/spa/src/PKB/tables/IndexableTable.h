#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include "PKB/data/Export.h"

namespace pkb {
using Key = std::variant<int, std::string>;
/// <summary>
/// Class for table indexable by id.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class IndexableTable {
 public:
  IndexableTable() = default;

  inline void add_row(Key v, T row) {
    indexes_.push_back(v);
    table_.insert(std::make_pair(v, row));
  }

  inline T &get_row(Key v) {
      return table_.at(v);
  }

  inline const T &get_row(Key v) const {
      return table_.at(v);
  }

  inline const std::vector<Key> &get_indexes() const {
    return indexes_;
  }

  inline std::vector<Key> &get_indexes() {
      return indexes_;
  }

  inline bool exists(Key v) const {
    return table_.find(v) != table_.end();
  }

  inline bool empty() {
      return table_.empty();
  }

  friend bool operator==(const IndexableTable &LHS, const IndexableTable &RHS) {
    if (LHS.get_indexes() != RHS.get_indexes()) return false;
    for (auto &index : LHS.get_indexes()) {
      if (!(LHS.get_row(index) == RHS.get_row(index))) return false;
    }
    return true;
  }

  std::unique_ptr<IndexableTable<T>> copy() {
    std::unique_ptr<IndexableTable<T>> result =
        std::make_unique<IndexableTable<T>>();
    result->table_ = table_;
    result->indexes_ = indexes_;
    return std::move(result);
  }

  inline void clear() {
    table_.clear();
    indexes_.clear();
  }

 protected:
  std::unordered_map<Key, T> table_;
  std::vector<Key> indexes_;
};

typedef IndexableTable<AffectsData> AffectsTable;
typedef IndexableTable<AffectsTData> AffectsTTable;
typedef IndexableTable<ModifiesData> ModifiesTable;
typedef IndexableTable<UsesData> UsesTable;
typedef IndexableTable<AssignData> AssignTable;
typedef IndexableTable<CallsData> CallsTable;
typedef IndexableTable<ConditionData> ConditionTable;

template <typename T>
using IndexableTablePtr = std::unique_ptr<IndexableTable<T>>;
}  // namespace pkb
