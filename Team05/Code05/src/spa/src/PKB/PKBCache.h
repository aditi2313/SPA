#pragma once

#include <unordered_set>

#include "PKB/data/AffectsData.h"
#include "PKB/tables/IndexableTable.h"

namespace pkb {
// Currently only stores Affects and AffectsT data
class PKBCache {
 public:
  inline bool ExistsAffects(int stmt) {
    return affects_table_.exists(stmt);
  }

  inline bool ExistsAffectsT(int stmt) {
    return affects_table_.exists(stmt)
        && affects_table_.get_row(stmt).is_affectsT_calculated();
  }

  inline void WriteAffects(int stmt, std::unordered_set<int> affected_lines) {
    affects_table_.add_row(stmt, AffectsData(stmt, affected_lines));
  }

  inline void WriteAffectsT(int stmt, std::unordered_set<int> affectedT_lines) {
    // Since AffectsT depends on Affects,
    // we can assume (and hence assert) that Affects has been
    // previously calculated for this stmt
    assert(ExistsAffects(stmt));
    affects_table_.get_row(stmt).set_affectedT_lines(affectedT_lines);
  }

  inline std::unordered_set<int> &GetAffects(int stmt) {
    return affects_table_.get_row(stmt).get_affected_lines();
  }

  inline std::unordered_set<int> &GetAffectsT(int stmt) {
    return affects_table_.get_row(stmt).get_affectedT_lines();
  }

  inline void clear() {
    affects_table_.clear();
  }

 private:
  AffectsTable affects_table_;
};
}  // namespace pkb

