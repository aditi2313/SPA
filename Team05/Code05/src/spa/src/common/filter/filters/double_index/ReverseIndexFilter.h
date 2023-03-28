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
    result_ = pkb::DoubleIndexReader<Data, Index, SecondIndex>(table);
    result_.AddSecondIndex(index_);
    return result_;
  }

  explicit ReverseIndexFilter(Index index) : index_(index) {}

 private:
  pkb::DoubleIndexReader<Data, Index, SecondIndex> result_;
  Index index_;
};
typedef ReverseIndexFilter<pkb::FollowsData> ReverseFollowFilter;

}  // namespace filter
