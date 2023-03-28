#pragma once

#include <exception>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "PKB/tables/DoubleIndexTable.h"
#include "PKB/tables/reader/DoubleIndexReader.h"
#include "PKB/tables/reader/IndexableReader.h"

namespace filter {
template <class Table, class Index, class Data>
class IndexDoubleFilter : public TableFilter<Table, Data> {
 public:
  pkb::TableReader<Data>& FilterTable(const Table& table) override {
    result_ = pkb::IndexableReader<Data, Table, Index>::of(table);
    if (!table.exists(index_)) {
      return *result_;
    }
    result_->AddIndex(index_);

    return *result_;
  }

  explicit IndexDoubleFilter(Index index) : index_(index) {}

 private:
  std::unique_ptr<pkb::IndexableReader<Data, Table, Index>> result_;
  Index index_;
};

typedef IndexDoubleFilter<pkb::CallsDTable, std::string, pkb::CallsData>
    CallsDIndexFilter;
typedef IndexDoubleFilter<pkb::ParentDTable, int, pkb::ParentData>
    ParentDIndexFilter;
typedef IndexDoubleFilter<pkb::FollowsDTable, int, pkb::FollowsData>
    FollowsDIndexFilter;
typedef IndexDoubleFilter<pkb::NextDTable, int, pkb::NextData> NextDIndexFilter;
}  // namespace filter
