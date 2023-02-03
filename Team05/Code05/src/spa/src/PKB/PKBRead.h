#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "PKBRelationTable.h"
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
  /// Ends the reading process, returning the pointer
  /// to the previous relation table.
  /// </summary>
  /// <returns></returns>
  std::unique_ptr<PKBRelationTable> EndRead() {
    read_end_ = true;
    return std::move(relation_table_);
  }

  /// <summary>
  /// Returns if the pkb read has ended.
  /// </summary>
  /// <returns></returns>
  bool hasEnded() { return read_end_; }

  /// <summary>
  /// Returns an indexable table for the modifies which satisfies the filter
  /// information.
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  IndexableTablePtr<ModifiesData> Modifies(IndexableFilterPtr<ModifiesData>);

 private:
  bool read_end_;
  std::unique_ptr<PKBRelationTable> relation_table_;
};

}  // namespace pkb
