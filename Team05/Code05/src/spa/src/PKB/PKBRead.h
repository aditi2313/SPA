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
  explicit PKBRead(std::unique_ptr<PKBRelationTable> relation_table) {
    relation_table_ = std::move(relation_table);
    read_end_ = false;
  }

  std::unique_ptr<PKBRelationTable> EndRead() {
    read_end_ = true;
    return std::move(relation_table_);
  }

  bool hasEnded() { return read_end_; }

  IndexableTablePtr<ModifiesData> Modifies(IndexableFilterPtr<ModifiesData>);

 private:
  bool read_end_;
  std::unique_ptr<PKBRelationTable> relation_table_;
};

}  // namespace pkb
