#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"
#include "PKB/data/CallsData.h"
#include "PKB/data/FollowsData.h"
#include "PKB/data/ModifiesData.h"
#include "PKB/data/ParentData.h"
#include "PKB/data/UsesData.h"
#include "PKB/tables/IndexableTable.h"
#include "common/exceptions/QPSExceptions.h"
#include "PKB/tables/reader/IndexableReader.h"

namespace filter {

template <class T>
class PredicateFilter : public IndexableFilter<T> {
 public:
  explicit PredicateFilter(std::function<bool(T)> predicate)
      : predicate_(predicate) {}

  inline pkb::IndexableTablePtr<T> FilterTable(
      const pkb::IndexableTable<T>& table) override {
    result_ = pkb::IndexableReader<T>(table);
    for (std::variant<int, std::string> line : table.get_indexes()) {
      auto data = table.get_row(line);
      if (predicate_(data)) {
        result_.AddIndex(line);
      }
    }
    return result_;
  }

 private:
  std::function<bool(T)> predicate_;
  pkb::IndexableReader<T> result_;
};

using ModifiesPredicateFilter = PredicateFilter<pkb::ModifiesData>;
using UsesPredicateFilter = PredicateFilter<pkb::UsesData>;
using FollowsPredicateFilter = PredicateFilter<pkb::FollowsData>;
using ParentPredicateFilter = PredicateFilter<pkb::ParentData>;
using AssignPredicateFilter = PredicateFilter<pkb::AssignData>;
using CallsPredicateFilter = PredicateFilter<pkb::CallsData>;
using NextPredicateFilter = PredicateFilter<pkb::NextData>;
}  // namespace filter
