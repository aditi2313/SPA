#pragma once

#include <memory>
#include <vector>

namespace filter {

template <class Table>
class TableFilter {
 public:
  /// <summary>
  /// Filters the given table and returns a vector of the results.
  /// </summary>
  /// <returns>The table with the filtered results</returns>
  virtual Table& FilterTable(const Table&) = 0;

  virtual ~TableFilter() = default;
};

}  // namespace filter
