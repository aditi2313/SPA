#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"
#include "PKB/data/CallsData.h"
#include "PKB/data/FollowsData.h"
#include "PKB/data/ModifiesData.h"
#include "PKB/data/ParentData.h"
#include "PKB/data/UsesData.h"
#include "PKB/tables/IndexableTable.h"
#include "PKB/tables/reader/IndexableReader.h"
#include "common/exceptions/QPSExceptions.h"

namespace filter {

template <class T>
class IndexFilter : public IndexableFilter<T> {
 public:
  explicit IndexFilter(std::variant<int, std::string> line) : line_(line) {}

  inline pkb::IndexableReader<T>& FilterTable(
      const pkb::IndexableTable<T>& table) override {
    result_ = pkb::IndexableReader<T>(table);
    result_.AddIndex(line_);
    return result_;
  }

  static std::unique_ptr<IndexFilter<T>> of(
      std::variant<int, std::string> line) {
    return std::make_unique<IndexFilter<T>>(line);
  }

 private:
  pkb::IndexableReader<T> result_;
  std::variant<int, std::string> line_;
};

using ModifiesIndexFilter = IndexFilter<pkb::ModifiesData>;
using AssignIndexFilter = IndexFilter<pkb::AssignData>;
using UsesIndexFilter = IndexFilter<pkb::UsesData>;
using FollowsIndexFilter = IndexFilter<pkb::FollowsData>;
using ParentIndexFilter = IndexFilter<pkb::ParentData>;
using CallsIndexFilter = IndexFilter<pkb::CallsData>;
using ConditionIndexFilter = IndexFilter<pkb::ConditionData>;
using NextIndexFilter = IndexFilter<pkb::NextData>;
}  // namespace filter
