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
#include "PKB/data/UsesData.h"
#include "PKB/data/FollowsData.h"
#include "PKB/data/ParentData.h"

namespace filter {

template<class T>
class IndexFilter
    : public IndexableFilter<T> {
 public:
  explicit IndexFilter(int line) : line_(line) {}

  inline pkb::IndexableTablePtr<T>
  FilterTable(pkb::IndexableTablePtr<T> table) override {
    pkb::IndexableTablePtr<T> result =
        std::make_unique<pkb::IndexableTable<T>>();
    if (table->exists(line_)) {
      auto row = table->get_row(line_);
      result->add_row(row.get_line(), row);
    }
    return result;
  }

 private:
  int line_;
};

using ModifiesIndexFilter = IndexFilter<pkb::ModifiesData>;
using AssignIndexFilter = IndexFilter<pkb::AssignData>;
using UsesIndexFilter = IndexFilter<pkb::UsesData>;
using FollowsIndexFilter = IndexFilter<pkb::FollowsData>;
using ParentIndexFilter = IndexFilter<pkb::ParentData>;
}  // namespace filter
