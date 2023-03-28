#pragma once

#include <memory>
#include <vector>

#include "PKB/tables/IndexableTable.h"
#include "TableReader.h"

namespace pkb {

template <class Data, class Table = IndexableTable<Data>, class Index = Key>
class IndexableReader : public TableReader<Data> {
 public:
  IndexableReader(const Table& table) : table_(&table) { ptr_ = keys_.begin(); }
  IndexableReader() : table_(nullptr) { ptr_ = keys_.begin(); }

  inline const Data& read_data() override { return table_->get_row(*ptr_); }

  inline void increment() override { ptr_++; }
  inline bool reached_end() override { return ptr_ == keys_.end(); }


  /// <summary>
  /// Adds an index and resets the
  /// ptr.
  /// </summary>
  /// <param name="key"></param>
  inline void AddIndex(Index key) {
    keys_.push_back(key);
    ptr_ = keys_.begin();
  }

  inline static std::unique_ptr<IndexableReader<Data, Table, Index>> of(
      const Table& table) {
    return std::make_unique<IndexableReader<Data, Table, Index>>(table);
  }

 private:
  const Table* table_;
  std::vector<Index> keys_;
  typename std::vector<Index>::iterator ptr_;
};

}  // namespace pkb
