#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"
#include "PKB/tables/IndexableTable.h"
#include "common/Exceptions.h"

namespace filter {

template<class T>
class IndexFilter
    : public IndexableFilter<T> {
 public:
  explicit IndexFilter(int line) : line_(line) {}

  pkb::IndexableTablePtr<T> FilterTable(pkb::IndexableTablePtr<T> table)
  override {
    pkb::IndexableTablePtr<T> result =
        std::make_unique<pkb::IndexableTable<T>>();
    auto row = table->get_row(line_);
    result->add_row(row.get_line(), row);
    return result;
  }

 private:
  int line_;
};

using ModifiesIndexFilter = IndexFilter<pkb::ModifiesData>;
using AssignIndexFilter = IndexFilter<pkb::AssignData>;

}  // namespace filter
