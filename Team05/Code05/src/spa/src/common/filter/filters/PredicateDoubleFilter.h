#pragma once

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "PKB/data/Export.h"
#include "PKB/tables/IndexableTable.h"
#include "PKB/tables/reader/IndexableReader.h"
#include "TableFilter.h"

namespace filter {

template <class Table, class Data, class Index = pkb::Key>
class PredicateDoubleFilter : public TableFilter<Table, Data> {
 public:
  explicit PredicateDoubleFilter(std::function<bool(Data)> predicate)
      : predicate_(predicate) {}

  inline pkb::TableReader<Data>& FilterTable(const Table& table) override {
    result_ = pkb::IndexableReader<Data, Table, Index>(table);
    for (Index line : table.get_indexes()) {
      auto data = table.get_row(line);
      if (predicate_(data)) {
        result_.AddIndex(line);
      }
    }
    return result_;
  }

 private:
  std::function<bool(Data)> predicate_;
  pkb::IndexableReader<Data, Table, Index> result_;
};

using ModifiesPredicateFilter =
    PredicateDoubleFilter<pkb::ModifiesTable, pkb::ModifiesData>;
using UsesPredicateFilter =
    PredicateDoubleFilter<pkb::UsesTable, pkb::UsesData>;
using FollowsPredicateFilter =
    PredicateDoubleFilter<pkb::FollowsDTable, pkb::FollowsData, int>;
using ParentPredicateFilter =
    PredicateDoubleFilter<pkb::ParentDTable, pkb::ParentData, int>;
using AssignPredicateFilter =
    PredicateDoubleFilter<pkb::AssignTable, pkb::AssignData>;
using CallsPredicateFilter =
    PredicateDoubleFilter<pkb::CallsDTable, pkb::CallsData, std::string>;
using NextPredicateFilter =
    PredicateDoubleFilter<pkb::NextDTable, pkb::NextData, int>;
}  // namespace filter
