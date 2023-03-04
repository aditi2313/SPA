#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "PKB/data/AssignData.h"
#include "PKB/data/CallsData.h"
#include "PKB/data/FollowsData.h"
#include "PKB/data/ModifiesData.h"
#include "PKB/data/NextData.h"
#include "PKB/data/ParentData.h"
#include "PKB/data/UsesData.h"

namespace pkb {

/// <summary>
/// Class for table indexable by id.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class IndexableTable {
 public:
  using IntOrStringVariant = std::variant<int, std::string>;

  IndexableTable() = default;

  inline void add_row(IntOrStringVariant v, T row) {
    indexes_.insert(v);
    table_.insert(std::make_pair(v, row));
  }

  inline T &get_row(IntOrStringVariant v) { return table_.at(v); }

  inline std::unordered_set<IntOrStringVariant> &get_indexes() {
    return indexes_;
  }

  inline bool exists(IntOrStringVariant v) const {
    return table_.find(v) != table_.end();
  }

  inline bool empty() { return table_.empty(); }

  friend bool operator==(const IndexableTable &LHS, const IndexableTable &RHS) {
    for (auto &[key, value] : LHS.table_) {
      if (!RHS.exists(key)) {
        return false;
      }
      const T val = RHS.table_.at(key);
      if (!(val == value)) return false;
    }
    for (auto &[key, value] : RHS.table_) {
      if (!LHS.exists(key)) {
        return false;
      }
      const T val = LHS.table_.at(key);
      if (!(val == value)) return false;
    }
    return true;
  }

  std::unique_ptr<IndexableTable<T>> copy() {
    std::unique_ptr<IndexableTable<T>> result =
        std::make_unique<IndexableTable<T>>();
    result->table_ = table_;
    return std::move(result);
  }

 protected:
  std::unordered_map<IntOrStringVariant, T> table_;
  std::unordered_set<IntOrStringVariant> indexes_;
};

typedef IndexableTable<ModifiesData> ModifiesTable;
typedef IndexableTable<UsesData> UsesTable;
typedef IndexableTable<FollowsData> FollowsTable;
typedef IndexableTable<ParentData> ParentTable;
typedef IndexableTable<AssignData> AssignTable;
typedef IndexableTable<CallsData> CallsTable;
typedef IndexableTable<NextData> NextTable;

template <typename T>
using IndexableTablePtr = std::unique_ptr<IndexableTable<T>>;
}  // namespace pkb
