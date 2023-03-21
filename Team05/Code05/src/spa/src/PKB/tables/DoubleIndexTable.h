#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "IndexableTable.h"
#include "PKB/data/Export.h"

namespace pkb {

// Double index table where we assume that the first index is the primary
// key and hence uniquely identifiable, and the secondary index is not uniquely
// identifiable.
template <class Data, class Index = Key, class SecondIndex = Key>
class DoubleIndexTable {
 public:
  DoubleIndexTable() {}

  inline void add_row(Index id, SecondIndex id2, Data& data) {
    // deal with case where the data exists with id
    if (exists(id)) {
      int index = first_index_map_.at(id);
      second_index_map_[id2].insert(index);
      return;
    }
    data_.push_back(data);
    first_index_map_[id] = data_.size() - 1;
    second_index_map_[id2] = data_.size() - 1;
  }

  inline void add_row(Index id, std::unordered_set<SecondIndex>& indexes,
                      Data data) {
    int index;
    if (exists(id)) {
      index = first_index_map_.at(id);
    } else {
      index = data_.size();
      data_.push_back(data);
    }
    for (auto& index2 : indexes) {
      second_index_map_[index2].insert(index);
    }
  }

  inline bool exists(Index id) { return first_index_map_.count(id); }

  inline bool exists2(SecondIndex id) {
    return second_index_map_.count(id) && !second_index_map_.at(id).empty();
  }

  inline Data& get_row(Index id) {
    return data_.at(first_index_map_.at(id).at(0));
  }

  inline std::vector<Data> get_rows(Index id) {
    std::vector<Data> result;
    for (int index : first_index_map_.at(id)) {
      result.push_back(data_.at(index));
    }
    return result;
  }

  inline Data& get_row_index2(SecondIndex id) {
    return data_.at(second_index_map_.at(id));
  }

  inline bool empty() { return data_.empty(); }

 protected:
  std::unordered_map<Index, int> first_index_map_;
  std::unordered_map<SecondIndex, std::unordered_set<int>> second_index_map_;
  std::vector<Data> data_;
};

using FollowsRTable = DoubleIndexTable<FollowsData, int, int>;

}  // namespace pkb
