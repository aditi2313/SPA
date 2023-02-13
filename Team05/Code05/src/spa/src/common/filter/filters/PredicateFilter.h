#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <functional>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"
#include "PKB/tables/IndexableTable.h"
#include "common/Exceptions.h"

namespace filter {

template <class T>
class PredicateFilter : public IndexableFilter<T> {
 public:
  explicit PredicateFilter(std::function<bool(T)> predicate)
      : predicate_(predicate) {}

  inline pkb::IndexableTablePtr<T> FilterTable(
      pkb::IndexableTablePtr<T> table) override {
    pkb::IndexableTablePtr<T> result =
        std::make_unique<pkb::IndexableTable<T>>();

    for (int line : table->get_indexes()) {
      auto data = table->get_row(line);
      if (predicate_(data)) {
        result->add_row(line, data);
      }
    }
    return std::move(result);
  }

 private:
  std::function<bool(T)> predicate_;
};

using ModifiesPredicateFilter = PredicateFilter<pkb::ModifiesData>;
using AssignPredicateFilter = PredicateFilter<pkb::AssignData>;
}  // namespace filter
