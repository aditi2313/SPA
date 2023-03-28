#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <string>

#include "IndexableTable.h"
#include "PKB/data/Export.h"

namespace pkb {

// Double index table where we assume that the first index is the primary
// key and hence uniquely identifiable, and the secondary index is not uniquely
// identifiable.
template <class Data, class Index = Key, class SecondIndex = Key>
class DoubleIndexTable {
  using CurrentTable = DoubleIndexTable<Data, Index, SecondIndex>;
  using CurrTablePtr = std::unique_ptr<CurrentTable>;

 public:
  DoubleIndexTable() {}

  inline void add_row(const Index& id, const SecondIndex& id2, Data& data) {
    // deal with case where the data exists with id
    if (exists(id)) {
      int index = first_index_map_.at(id);
      second_index_map_[id2].insert(index);
      return;
    }
    data_.push_back(data);
    first_index_map_[id] = data_.size() - 1;
    second_index_map_[id2].insert(data_.size() - 1);
  }

  template <class IterableSecondIndex>
  inline void add_row(Index id, IterableSecondIndex& indexes, Data data) {
    int index;
    if (exists(id)) {
      index = first_index_map_.at(id);
    } else {
      index = data_.size();
      first_index_map_[id] = index;
      data_.push_back(data);
    }
    for (auto& index2 : indexes) {
      second_index_map_[index2].insert(index);
    }
  }

  inline bool exists(Index id) const { return first_index_map_.count(id); }

  inline bool exists(const Index& id, const SecondIndex& id2) {
    return exists(id) && exists2(id2) &&
           get_row(id).get_second_indexes().count(id2);
  }

  inline bool exists2(SecondIndex id) const {
    return second_index_map_.count(id) && !second_index_map_.at(id).empty();
  }

  inline const Data& get_row(Index id) const {
    return data_.at(first_index_map_.at(id));
  }
  inline Data& get_row(Index id) { return data_.at(first_index_map_.at(id)); }

  inline std::vector<Index> get_row_index2(SecondIndex id) const {
    std::vector<Index> result;
    int size = second_index_map_.at(id).size();
    result.reserve(size);
    for (int index : second_index_map_.at(id)) {
      result.push_back(data_.at(index).get_index());
    }
    return result;
  }

  inline bool empty() const { return data_.empty(); }

  friend bool operator==(
      const DoubleIndexTable<Data, Index, SecondIndex>& LHS,
      const DoubleIndexTable<Data, Index, SecondIndex>& RHS) {
    if (LHS.data_.size() != RHS.data_.size()) return false;
    for (auto& [id, index] : LHS.first_index_map_) {
      if (LHS.get_row(id) != RHS.get_row(id)) {
        return false;
      }
    }
    for (auto& [sid, indexes] : LHS.second_index_map_) {
      if (LHS.get_row_index2(sid) != RHS.get_row_index2(sid)) {
        return false;
      }
    }
    return true;
  }

 protected:
  std::unordered_map<Index, int> first_index_map_;
  std::unordered_map<SecondIndex, std::unordered_set<int>> second_index_map_;
  std::vector<Data> data_;
};

typedef DoubleIndexTable<NextData, int, int> NextDTable;
typedef DoubleIndexTable<FollowsData, int, int> FollowsDTable;
typedef DoubleIndexTable<ParentData, int, int> ParentDTable;
typedef DoubleIndexTable<CallsData, std::string, std::string> CallsDTable;

}  // namespace pkb
