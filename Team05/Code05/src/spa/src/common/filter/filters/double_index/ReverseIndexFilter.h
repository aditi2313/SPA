#pragma once

#include "TableFilter.h"

namespace filter {
template <class Data, class Index = int, class SecondIndex = int>
class ReverseIndexFilter
    : public TableFilter<pkb::DoubleIndexTable<Data, Index, SecondIndex>,
                         Data> {
  using Table = pkb::DoubleIndexTable<Data, Index, SecondIndex>;

 public:
  pkb::TableReader<Data>& FilterTable(const Table& table) override {
    result_ = pkb::DoubleIndexReader<Data, Index, SecondIndex>::of(table);
    result_->AddSecondIndex(index_);
    return *result_;
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

  explicit ReverseIndexFilter(Index index) : index_(index) {}

 private:
  inline static std::unordered_map<
      Index, std::unique_ptr<ReverseIndexFilter<Table, Index>>>
      filters_;

  std::unique_ptr<pkb::DoubleIndexReader<Data, Index, SecondIndex>> result_;
  Index index_;
};
typedef ReverseIndexFilter<pkb::FollowsData> ReverseFollowFilter;

}  // namespace filter
