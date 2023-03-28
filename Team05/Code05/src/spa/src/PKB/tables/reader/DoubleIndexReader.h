#pragma once

#include <memory>
#include <vector>

#include "PKB/PKBRead.h"
#include "TableReader.h"

namespace pkb {
template <class Data, class Index, class SecondIndex>
class DoubleIndexReader : public TableReader<Data> {
 public:
  DoubleIndexReader(DoubleIndexTable<Data, Index, SecondIndex>& table)
      : table_(table) {
    ptr_ = indexes_.begin();
  }

  inline const Data& read_data() override { return table_.data_.at(*ptr_); }

  inline void increment() override { ptr_++; }

  inline void reached_end() override { return ptr_ == indexes_.end(); }

  inline void AddIndex(Index index) {
    int index = table_.first_index_map_.at(index);
    indexes_.push_back(index);
  }

  inline void AddSecondIndex(SecondIndex s_index) {
    auto& s_indexes = table_.second_index_map_.at(s_index);
    for (auto index : s_indexes) {
      indexes_.push_back(index);
    }
  }

  inline static std::unique_ptr<DoubleIndexReader<Data, Index, SecondIndex>> of(
      DoubleIndexTable<Data, Index, SecondIndex>& table) {
    return std::make_unique<DoubleIndexReader<Data, Index, SecondIndex>>(
        DoubleIndexReader<Data, Index, SecondIndex>(table))
  }

 private:
  std::vector<int> indexes_;
  std::vector<int>::iterator ptr_;
  DoubleIndexTable<Data, Index, SecondIndex>& table_;
};

}  // namespace pkb
