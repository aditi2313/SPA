#pragma once

#include <unordered_set>

#include "PKB/data/AffectsData.h"
#include "PKB/tables/IndexableTable.h"
#include "PKB/tables/DoubleIndexTable.h"

namespace pkb {
// Currently only stores Affects and AffectsT data
class PKBCache {
 public:
  inline bool ExistsAffects(Line stmt) {
    return affects_d_table_.exists(stmt);
  }

  inline bool ExistsReverseAffects(Line stmt) {
    if(!is_all_affects_cached_) return false;
    return affects_d_table_.exists2(stmt);
  }

  inline bool ExistsAffectsT(Line stmt) {
    return affectsT_table_.exists(stmt);
  }

  inline void WriteAffects(Line stmt, LineSet affected_lines) {
    AffectsData affects_data(stmt, affected_lines);
    affects_d_table_.add_row(stmt, affected_lines, affects_data);
  }

  inline void WriteAffectsT(Line stmt, LineSet affectedT_lines) {
    affectsT_table_.add_row(stmt, AffectsTData(stmt, affectedT_lines));
  }

  inline LineSet &GetAffects(Line stmt) {
    return affects_d_table_.get_row(stmt).get_affected_lines();
  }

  inline LineSet GetReverseAffects(Line stmt) {
    return affects_d_table_.get_row_index2(stmt);
  }

  inline LineSet &GetAffectsT(Line stmt) {
    return affectsT_table_.get_row(stmt).get_affected_lines();
  }

  inline void clear() {
    is_all_affects_cached_ = false;
    affects_d_table_.clear();
    affectsT_table_.clear();
  }

  inline bool is_all_affects_cached() {
    return is_all_affects_cached_;
  }

  inline void set_all_affects_cached_to_true() {
    is_all_affects_cached_ = true;
  }

 private:
  AffectsDTable affects_d_table_;
  AffectsTTable affectsT_table_;
  // True iff affects for all assign statements have
  // been calculated
  bool is_all_affects_cached_ = false;
};
}  // namespace pkb

