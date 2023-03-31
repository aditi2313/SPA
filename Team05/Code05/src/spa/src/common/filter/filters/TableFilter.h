
#pragma once

#include <exception>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "PKB/tables/DoubleIndexTable.h"
#include "PKB/tables/reader/DoubleIndexReader.h"
#include "PKB/tables/reader/TableReader.h"

namespace filter {

template <class Table, class Data>
class TableFilter {
 public:
  /// <summary>
  /// Filters the given table and returns a vector of the results.
  /// </summary>
  /// <returns>The table with the filtered results</returns>
  virtual pkb::TableReader<Data>& FilterTable(const Table&) = 0;

  virtual ~TableFilter() = default;
};
typedef TableFilter<pkb::CallsDTable, pkb::CallsData> CallsTableFilter;
typedef TableFilter<pkb::ParentDTable, pkb::ParentData> ParentTableFilter;
typedef TableFilter<pkb::FollowsDTable, pkb::FollowsData> FollowsTableFilter;
typedef TableFilter<pkb::NextDTable, pkb::NextData> NextTableFilter;
typedef TableFilter<pkb::ModifiesTable, pkb::ModifiesData> ModifiesTableFilter;
typedef TableFilter<pkb::AffectsTable, pkb::AffectsData> AffectsTableFilter;
typedef TableFilter<pkb::ConditionTable, pkb::ConditionData>
    ConditionTableFilter;
typedef TableFilter<pkb::UsesTable, pkb::UsesData> UsesTableFilter;
typedef TableFilter<pkb::AssignTable, pkb::AssignData> AssignTableFilter;

}  // namespace filter
