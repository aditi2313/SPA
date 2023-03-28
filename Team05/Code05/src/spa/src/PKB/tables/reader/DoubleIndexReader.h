#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IndexableReader.h"
#include "TableReader.h"

namespace pkb {
template <class Data, class Index, class SecondIndex>
class DoubleIndexReader : public TableReader<Data> {
 public:
  DoubleIndexReader(const DoubleIndexTable<Data, Index, SecondIndex>& table)
      : table_(&table) {
    ptr_ = indexes_.begin();
  }

  DoubleIndexReader() {
    table_ = nullptr;
    ptr_ = indexes_.begin();
  }

  inline const Data& read_data() override { return table_->data_.at(*ptr_); }

  inline void increment() override { ptr_++; }

  inline bool reached_end() override { return ptr_ == indexes_.end(); }

  inline void AddIndex(Index index) {
    if (!table_->first_index_map_.count(index)) return;
    int id = table_->first_index_map_.at(index);
    indexes_.push_back(id);
    ptr_ = keys_.begin();
  }

  inline void AddSecondIndex(SecondIndex s_index) {
    if (!table_->second_index_map_.count(s_index)) return;
    auto& s_indexes = table_->second_index_map_.at(s_index);
    for (auto index : s_indexes) {
      indexes_.push_back(index);
    }
  }

  inline static std::unique_ptr<DoubleIndexReader<Data, Index, SecondIndex>> of(
      const DoubleIndexTable<Data, Index, SecondIndex>& table) {
    return std::make_unique<DoubleIndexReader<Data, Index, SecondIndex>>(
        DoubleIndexReader<Data, Index, SecondIndex>(table));
  }

 private:
  std::vector<int> indexes_;
  std::vector<int>::iterator ptr_;
  const DoubleIndexTable<Data, Index, SecondIndex>* table_;
};

typedef DoubleIndexReader<CallsData, std::string, std::string> CallTableReader;
typedef DoubleIndexReader<ParentData, int, int> ParentTableReader;

}  // namespace pkb
