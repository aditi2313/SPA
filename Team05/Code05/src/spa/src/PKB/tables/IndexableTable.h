#pragma once

#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <variant>
#include <string>

#include "PKB/data/AssignData.h"
#include "PKB/data/ModifiesData.h"
#include "PKB/data/UsesData.h"
#include "PKB/data/FollowsData.h"
#include "PKB/data/ParentData.h"
#include "PKB/data/CallsData.h"
#include "PKB/tables/IndexableTable.h"

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
    id_map_[v] = rows_.size();
    rows_.push_back(std::move(row));
  }

  inline T& get_row(IntOrStringVariant v) { return rows_.at(id_map_.at(v)); }

  inline std::set<IntOrStringVariant> get_indexes() {
    std::set<IntOrStringVariant> result;
    for (auto &[v, row] : id_map_) {
      result.insert(v);
    }
    return result;
  }

  inline bool exists(IntOrStringVariant v) {
      return id_map_.find(v) != id_map_.end();
  }

  inline bool empty() { return rows_.empty(); }

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
  std::unordered_map<std::variant<int, std::string>, int> id_map_;
};

typedef IndexableTable<ModifiesData> ModifiesTable;
typedef IndexableTable<UsesData> UsesTable;
typedef IndexableTable<FollowsData> FollowsTable;
typedef IndexableTable<ParentData> ParentTable;
typedef IndexableTable<AssignData> AssignTable;
typedef IndexableTable<CallsData> CallsTable;

template <typename T>
using IndexableTablePtr = std::unique_ptr<IndexableTable<T>>;
}  // namespace pkb
