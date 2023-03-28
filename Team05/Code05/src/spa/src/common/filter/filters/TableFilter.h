
#pragma once

#include <exception>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "PKB/tables/reader/TableReader.h"
#include "PKB/tables/DoubleIndexTable.h"

namespace filter {

template <class Table>
class TableFilter {
 public:
  /// <summary>
  /// Filters the given table and returns a vector of the results.
  /// </summary>
  /// <returns>The table with the filtered results</returns>
  virtual Table& FilterTable(const Table&) = 0;

  virtual ~TableFilter() = default;
};
typedef TableFilter<pkb::CallsDTable> CallsTableFilter;
typedef TableFilter<pkb::ParentDTable> ParentTableFilter;
typedef TableFilter<pkb::FollowsDTable> FollowsTableFilter;
typedef TableFilter<pkb::NextDTable> NextTableFilter;

template <class Table, class Index>
class ReverseIndexFilter : public TableFilter<Table> {
 public:
  Table& FilterTable(const Table& table) override {
    result_ = Table();
    auto datas = table.get_row_index2(index_);
    for (auto& data : datas) {
      //result_.add_row(data.get_index(), index_, data);
    }
    return result_;
  }

  // needed to store the result table.
  inline static ReverseIndexFilter<Table, Index>& of(Index index) {
    if (!filters_.count(index)) {
      ReverseIndexFilter filter(index);
      filters_.insert(
          {index, std::make_unique<ReverseIndexFilter<Table, Index>>(filter)});
    }
    return *filters_.at(index);
  }

 private:
  explicit ReverseIndexFilter(Index index) : index_(index) {}

  inline static std::unordered_map<
      Index, std::unique_ptr<ReverseIndexFilter<Table, Index>>>
      filters_;
  Table result_;
  Index index_;
};
typedef ReverseIndexFilter<pkb::FollowsDTable, int> ReverseFollowFilter;

template <class Table, class Index>
class IndexDoubleFilter : public TableFilter<Table> {
 public:
  Table& FilterTable(const Table& table) override {
    result_ = Table();
    if (!table.exists(index_)) {
      return result_;
    }
    auto& data = table.get_row(index_);
    // todo(gab): this might actually perform worse than current though,
    // we are adding for all the second indexes
    result_.add_row(index_, data.get_second_indexes(), data);
    return result_;
  }

  inline static IndexDoubleFilter<Table, Index>& of(Index index) {
    if (!filters_.count(index)) {
      IndexDoubleFilter filter(index);
      filters_.insert(
          {index, std::make_unique<IndexDoubleFilter<Table, Index>>(filter)});
    }
    return *filters_.at(index);
  }

 private:
  explicit IndexDoubleFilter(Index index) : index_(index) {}
  inline static std::unordered_map<
      Index, std::unique_ptr<IndexDoubleFilter<Table, Index>>>
      filters_;
  Table result_;
  Index index_;
};

typedef IndexDoubleFilter<pkb::CallsDTable, std::string> CallsDIndexFilter;
typedef IndexDoubleFilter<pkb::ParentDTable, int> ParentDIndexFilter;
typedef IndexDoubleFilter<pkb::FollowsDTable, int> FollowsDIndexFilter;
typedef IndexDoubleFilter<pkb::NextDTable, int> NextDIndexFilter;

}  // namespace filter
