#pragma once

#include <memory>
#include <vector>

#include "PKB/tables/Table.h"

namespace filter {

template <class T>
class Filter {
 public:
  /// <summary>
  /// Filters the given table and returns a vector of the results.
  /// </summary>
  /// <returns></returns>
  virtual std::unique_ptr<pkb::Table<T>> FilterTable(
      std::unique_ptr<pkb::Table<T>>) = 0;
};

}  // namespace filter
