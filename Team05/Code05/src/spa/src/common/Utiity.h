#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <list>
#include <iostream>

namespace util {
// Todo(Gab) replace all dynamic cast checks with this.

/// <summary>
/// Utility function for checking the instance of a
/// object.
/// </summary>
/// <typeparam name="Base">The base class of the object.</typeparam>
/// <typeparam name="Derived">The possibly derived class of the
/// object.</typeparam> <param name="other">The object to check</param>
/// <returns></returns>
template<class Derived, class Base>
inline bool InstanceOf(const Base &object) {
  return dynamic_cast<const Derived *>(&object) != nullptr;
}

/// <summary>
/// Utility function for comparing between two vectors of
/// unique pointers
/// </summary>
/// <returns>True if the two vectors are the same size and
/// the object each pointer is pointing to compares equal</returns>
template<class UniquePointerLHS, class UniquePointerRHS>
inline bool CompareVectorOfPointers(const std::vector<UniquePointerLHS> &LHS,
                                    const std::vector<UniquePointerRHS> &RHS) {
  if (LHS.size() != RHS.size()) return false;
  for (int N = LHS.size(), i = 0; i < N; ++i) {
    if (*(LHS.at(i)) != *(RHS.at(i))) return false;
  }
  return true;
}

/// <summary>
/// Utility function for comparing between two results
/// </summary>
/// <returns>True if the two results have the same strings
/// regardless of order</returns>
inline bool CompareResults(const std::list<std::string> &LHS,
                           const std::list<std::string> &RHS) {
  std::unordered_map<std::string, int> LHS_map, RHS_map;
  for (auto &res : LHS) {
    LHS_map[res]++;
  }
  for (auto &res : RHS) {
    RHS_map[res]++;
  }

  return LHS_map == RHS_map;
}
}  // namespace util
