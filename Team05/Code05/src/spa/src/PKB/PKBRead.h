#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKBCache.h"
#include "PKBRelationTable.h"
#include "common/filter/filters/TableFilter.h"
#include "tables/DoubleIndexTable.h"

namespace pkb {
class PKBRead {
 public:
  /// <summary>
  /// Create a PKBRead which reads from the given relation table.
  /// </summary>
  /// <param name="relation_table">The table containing all
  /// relationships</param>
  explicit PKBRead(std::unique_ptr<PKBRelationTable> relation_table) {
    relation_table_ = std::move(relation_table);
    // Create new cache if not using passed in cache
    cache_ = std::make_unique<PKBCache>();
    read_end_ = false;
  }

  /// <summary>
  /// Create a PKBRead which reads from the given relation table
  /// and cache.
  /// </summary>
  /// <param name="relation_table">The table containing all
  /// relationships</param>
  /// <param name="cache"> Cache that may contain
  /// previously computed data from other queries</param>
  PKBRead(std::unique_ptr<PKBRelationTable> relation_table,
          std::unique_ptr<PKBCache> cache) {
    relation_table_ = std::move(relation_table);
    cache_ = std::move(cache);
    read_end_ = false;
  }

  std::unique_ptr<PKBRelationTable> EndRead() {
    return std::move(relation_table_);
  }

  std::unique_ptr<PKBCache> RetrieveCache() {
      return std::move(cache_);
  }

  inline void ClearCache() {
    cache_->clear();
  }

  /// <summary>
  /// Returns if the pkb read has ended.
  /// </summary>
  /// <returns></returns>
  inline bool HasEnded() {
      return read_end_;
  }

  /// <summary>
  /// Returns an indexable table for the modifies which satisfies the filter
  /// information.
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  ModifiesDataReader& Modifies(filter::ModifiesTableFilter&);

  AssignDataReader& Assigns(filter::AssignTableFilter&);

  UsesDataReader& Uses(filter::UsesTableFilter&);

  LineSet NextT(Line);
  LineSet ReverseNextT(Line);

  ConditionDataReader& Condition(filter::ConditionTableFilter&);

  VarSet get_variables() {
    return relation_table_->variables_;
  }

  LineSet get_constants() {
    return relation_table_->constants_;
  }

  const LineSet& get_whiles() {
    return relation_table_->whiles_;
  }

  const LineSet& get_stmts() {
      return relation_table_->stmts_;
  }

  const LineSet& get_calls() {
      return relation_table_->calls_;
  }

  const LineSet& get_assign() {
      return relation_table_->assign_;
  }

  const LineSet& get_print() {
      return relation_table_->print_;
  }

  const LineSet& get_read() {
      return relation_table_->read_;
  }

  const LineSet& get_if() {
      return relation_table_->if_;
  }

  const ProcSet& get_procedures() {
    return relation_table_->procedures_;
  }

  const Var get_var_name_from_line(Line line) {
    return relation_table_->line_to_var_name_[line];
  }

  const Proc get_proc_name_from_line(Line line) {
    return relation_table_->line_to_proc_name_[line];
  }

  void CacheAllAffects();

  LineSet Affects(Line);
  LineSet ReverseAffects(Line);

  LineSet AffectsT(Line);

  CallsDataReader& Calls(filter::CallsTableFilter& ftr) {
    return ftr.FilterTable(relation_table_->calls_d_table_);
  }

  ParentDataReader& Parent(filter::ParentTableFilter& ftr) {
    return ftr.FilterTable(relation_table_->parent_d_table_);
  }

  FollowsDataReader& Follows(filter::FollowsTableFilter& ftr) {
    return ftr.FilterTable(relation_table_->follows_d_table_);
  }

  NextDataReader& Next(filter::NextTableFilter& ftr) {
    return ftr.FilterTable(relation_table_->next_d_table_);
  }

 private:
  inline bool IsContainerStmt(Line v) {
    return relation_table_->if_.count(v) || relation_table_->whiles_.count(v);
  }

  bool read_end_;
  std::unique_ptr<PKBRelationTable> relation_table_;
  std::unique_ptr<PKBCache> cache_;
};

using PKBReadPtr = std::unique_ptr<PKBRead>;
}  // namespace pkb
