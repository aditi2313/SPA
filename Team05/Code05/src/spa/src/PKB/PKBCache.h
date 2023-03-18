#pragma once

#include <unordered_set>

#include "PKB/data/AffectsData.h"
#include "PKB/tables/IndexableTable.h"

namespace pkb {
// Currently only stores Affects* data
class PKBCache {
 public:
  inline bool exists(int stmt) {
    return affects_table_.exists(stmt);
  }

  inline void WriteAffects(int stmt, std::unordered_set<int> affected_lines) {
    affects_table_.add_row(stmt, AffectsData(stmt, affected_lines));
  }

  inline AffectsData GetAffects(int stmt) {
    return affects_table_.get_row(stmt);
  }

  inline void clear() {
    affects_table_.clear();
  }

 private:
  AffectsTable affects_table_;
};
}  // namespace pkb

