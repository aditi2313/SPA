#pragma once

#include <exception>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "PKB/data/Data.h"
#include "PKB/tables/DoubleIndexTable.h"
#include "PKB/tables/IndexableTable.h"
#include "PKB/tables/reader/IndexableReader.h"
#include "TableFilter.h"


namespace filter {
template <class Table, class Data, class Index = pkb::Key>
class IndexDoubleFilter : public TableFilter<Table, Data> {
 public:
  pkb::TableReader<Data>& FilterTable(const Table& table) override {
    result_ = pkb::IndexableReader<Data, Table, Index>(table);
    if (!table.exists(index_)) {
      return result_;
    }
    result_.AddIndex(index_);

    return result_;
  }

  explicit IndexDoubleFilter(Index index) : index_(index) {}

 private:
  pkb::IndexableReader<Data, Table, Index> result_;
  Index index_;
};

typedef IndexDoubleFilter<pkb::CallsDTable, pkb::CallsData, std::string>
    CallsIndexFilter;
typedef IndexDoubleFilter<pkb::ParentDTable, pkb::ParentData, int>
    ParentIndexFilter;
typedef IndexDoubleFilter<pkb::FollowsDTable, pkb::FollowsData, int>
    FollowsIndexFilter;
typedef IndexDoubleFilter<pkb::NextDTable, pkb::NextData, int> NextIndexFilter;
typedef IndexDoubleFilter<pkb::ModifiesTable, pkb::ModifiesData>
    ModifiesIndexFilter;
typedef IndexDoubleFilter<pkb::UsesTable, pkb::UsesData> UsesIndexFilter;

typedef IndexDoubleFilter<pkb::AssignTable, pkb::AssignData> AssignIndexFilter;

typedef IndexDoubleFilter<pkb::ConditionTable, pkb::ConditionData>
    ConditionIndexFilter;

}  // namespace filter
