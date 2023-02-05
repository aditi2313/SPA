#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "PKBRelationTable.h"
#include "PKBResult.h"
#include "common/filter/filters/IndexableFilter.h"
#include "common/filter/filters/ModifiesFilter.h"

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
    read_end_ = false;
  }

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
      IndexableFilterPtr<std::shared_ptr<AssignData>>);
  std::set<std::string> get_variables() { return relation_table_->variables_; }

  std::set<int> get_constants() { return relation_table_->constants_; }

  const std::set<int>& get_whiles() { return relation_table_->whiles_; }
  const std::set<int>& get_stmts() { return relation_table_->stmts_; }
  const std::set<int>& get_calls() { return relation_table_->calls_; }
  const std::set<int>& get_assign() { return relation_table_->assign_; }

  const std::set<std::string>& get_procedures() {
    return relation_table_->procedures_;
  }

 private:
  bool read_end_;
  std::unique_ptr<PKBRelationTable> relation_table_;
};

}  // namespace pkb
