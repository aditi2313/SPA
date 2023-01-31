#pragma once
#include "common/filter/filters/Filter.h"

namespace filter {

<typename T> class FilterBuilder {
 public:
  Filter<T> build() = 0;
};
}  // namespace filter
