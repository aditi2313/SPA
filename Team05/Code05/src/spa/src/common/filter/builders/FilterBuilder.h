#pragma once
#include "common/filter/filters/Filter.h"

namespace filter {

<typename T> class FilterBuilder {
 public:
  virtual Filter<T> Build() = 0;
};
}  // namespace filter
