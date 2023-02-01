#pragma once

#include <vector>


namespace filter {

template <class T> class Filter {
 public:
  /// <summary>
  /// Filters the given container and returns a vector of the results.
  /// TODO: change vector to Table.
  /// </summary>
  /// <returns></returns>
  virtual std::vector<T> Filter(std::vector<T>&) = 0;
};

}  // namespace filter
