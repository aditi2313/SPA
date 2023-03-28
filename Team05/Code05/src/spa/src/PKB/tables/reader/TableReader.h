#pragma once

#include <memory>
#include <vector>

namespace pkb {

// todo(Gab) use datawrapper when done by @aditi
template <class Data>
class TableReader {
 public:
  TableReader() {}
  virtual const Data& read_data() = 0;
  virtual void increment() = 0;
  virtual bool reached_end() = 0;
};

template <class Data>
using TableReaderPtr = std::unique_ptr<TableReader<Data>>;
typedef TableReader<FollowsData> FollowsDataReader;
typedef TableReader<ParentData> ParentDataReader;
typedef TableReader<NextData> NextDataReader;
typedef TableReader<CallsData> CallsDataReader;
typedef TableReader<AffectsData> AffectsDataReader;
typedef TableReader<AssignData> AssignDataReader;
typedef TableReader<ModifiesData> ModifiesDataReader;
typedef TableReader<UsesData> UsesDataReader;
typedef TableReader<ConditionData> ConditionDataReader;

}  // namespace pkb
