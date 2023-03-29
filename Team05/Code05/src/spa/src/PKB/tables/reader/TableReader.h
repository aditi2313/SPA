#pragma once

#include <memory>
#include <vector>

#include "PKB/data/Export.h"

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
typedef TableReader<pkb::FollowsData> FollowsDataReader;
typedef TableReader<pkb::ParentData> ParentDataReader;
typedef TableReader<pkb::NextData> NextDataReader;
typedef TableReader<pkb::CallsData> CallsDataReader;
typedef TableReader<pkb::AffectsData> AffectsDataReader;
typedef TableReader<pkb::AssignData> AssignDataReader;
typedef TableReader<pkb::ModifiesData> ModifiesDataReader;
typedef TableReader<pkb::UsesData> UsesDataReader;
typedef TableReader<pkb::ConditionData> ConditionDataReader;

}  // namespace pkb
