#pragma once

#include <functional>


template <class Data>
std::function<bool(Data data)> TruePredicate() {
  return ([](Data data) { return true; });
}
