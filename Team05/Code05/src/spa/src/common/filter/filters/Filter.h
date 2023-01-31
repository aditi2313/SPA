#pragma once

#include <vector>

namespace filter {

<typename T> class Filter<T> {
 public:
  /// <summary>
  /// Filters the given container and returns a vector of the results.
  /// TODO: change vector to Table.
  /// </summary>
  /// <returns></returns>
  std::vector<T> filter(std::container<T>&) = 0;
};

}  // namespace filter
