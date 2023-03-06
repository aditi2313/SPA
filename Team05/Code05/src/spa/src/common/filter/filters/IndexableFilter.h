#pragma once

#include <memory>
#include <vector>

#include "PKB/tables/IndexableTable.h"

namespace filter {

template <class T>
class IndexableFilter {
 public:
  /// <summary>
  /// Filters the given table and returns a vector of the results.
  /// </summary>
  /// <returns>The table with the filtered results</returns>
  virtual pkb::IndexableTablePtr<T> FilterTable(
      const pkb::IndexableTable<T> &) = 0;

  virtual ~IndexableFilter() = default;
};

template <class T>
using IndexableFilterPtr = std::unique_ptr<IndexableFilter<T>>;

}  // namespace filter
