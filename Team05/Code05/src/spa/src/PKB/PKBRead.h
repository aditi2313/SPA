#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKBCache.h"
#include "PKBRelationTable.h"
#include "PKBResult.h"
#include "common/filter/filters/IndexableFilter.h"
#include "common/filter/filters/TableTest.h"
#include "tables/DoubleIndexTable.h"

using filter::IndexableFilterPtr;

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

  std::unique_ptr<PKBCache> RetrieveCache() { return std::move(cache_); }

  /// <summary>
  /// Returns if the pkb read has ended.
  /// </summary>
  /// <returns></returns>
  inline bool HasEnded() { return read_end_; }

  /// <summary>
  /// Returns an indexable table for the modifies which satisfies the filter
  /// information.
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  std::unique_ptr<PKBResult<ModifiesTable>> Modifies(
      IndexableFilterPtr<ModifiesData>);

  std::unique_ptr<PKBResult<AssignTable>> Assigns(
      IndexableFilterPtr<AssignData>);

  std::unique_ptr<PKBResult<UsesTable>> Uses(IndexableFilterPtr<UsesData>);

  std::unique_ptr<PKBResult<FollowsTable>> Follows(
      IndexableFilterPtr<FollowsData>);

  std::unique_ptr<PKBResult<ParentTable>> Parent(
      IndexableFilterPtr<ParentData>);

  std::unordered_set<int> NextT(int);

  std::unique_ptr<PKBResult<CallsTable>> Calls(
      IndexableFilterPtr<CallsData> filter);

  std::unique_ptr<PKBResult<NextTable>> Next(IndexableFilterPtr<NextData>);

  std::unique_ptr<PKBResult<ConditionTable>> Condition(
      IndexableFilterPtr<ConditionData>);

  std::unordered_set<std::string> get_variables() {
    return relation_table_->variables_;
  }

  std::unordered_set<int> get_constants() {
    return relation_table_->constants_;
  }

  const std::unordered_set<int>& get_whiles() {
    return relation_table_->whiles_;
  }
  const std::unordered_set<int>& get_stmts() { return relation_table_->stmts_; }
  const std::unordered_set<int>& get_calls() { return relation_table_->calls_; }
  const std::unordered_set<int>& get_assign() {
    return relation_table_->assign_;
  }
  const std::unordered_set<int>& get_print() { return relation_table_->print_; }
  const std::unordered_set<int>& get_read() { return relation_table_->read_; }
  const std::unordered_set<int>& get_if() { return relation_table_->if_; }

  const std::unordered_set<std::string>& get_procedures() {
    return relation_table_->procedures_;
  }

  const std::string get_var_name_from_line(int line) {
    return relation_table_->line_to_var_name_[line];
  }

  const std::string get_proc_name_from_line(int line) {
    return relation_table_->line_to_proc_name_[line];
  }

  std::unordered_set<int> Affects(int);

  std::unordered_set<int> AffectsT(int);

  inline bool Calls(filter::TableTest<CallsDTable>& test) {
    return test.TestTable(relation_table_->calls_d_table_);
  }

 private:
  inline bool IsContainerStmt(int v) {
    return relation_table_->if_.count(v) || relation_table_->whiles_.count(v);
  }

  bool read_end_;
  std::unique_ptr<PKBRelationTable> relation_table_;
  std::unique_ptr<PKBCache> cache_;
};

using PKBReadPtr = std::unique_ptr<PKBRead>;
}  // namespace pkb
