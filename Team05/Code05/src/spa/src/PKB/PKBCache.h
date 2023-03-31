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
    return affectsT_table_.exists(stmt);
  }

  inline void WriteAffects(int stmt, LineSet affected_lines) {
    affects_table_.add_row(stmt, AffectsData(stmt, affected_lines));
  }

  inline void WriteAffectsT(int stmt, LineSet affectedT_lines) {
    affectsT_table_.add_row(stmt, AffectsTData(stmt, affectedT_lines));
  }

  inline LineSet &GetAffects(int stmt) {
    return affects_table_.get_row(stmt).get_affected_lines();
  }

  inline LineSet &GetAffectsT(int stmt) {
    return affectsT_table_.get_row(stmt).get_affected_lines();
  }

  inline void clear() {
    affects_table_.clear();
    affectsT_table_.clear();
  }

 private:
  AffectsTable affects_table_;
  AffectsTTable affectsT_table_;
};
}  // namespace pkb

