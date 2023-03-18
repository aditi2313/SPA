#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

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

  if (LHS_map != RHS_map) {
    std::cout << "actual: ";
    for (auto str : LHS) {
      std::cout << str << ", ";
    }
    std::cout << "\n";
    std::cout << "expected: ";
    for (auto str : RHS) {
      std::cout << str << ", ";
    }
    std::cout << "\n";
  }

  return LHS_map == RHS_map;
}

class BoundedInt {
 public:
  BoundedInt(int val, int max, int min) : min_(min), max_(max), val_(val) {}

  int operator*() const {
    if (ExceedBound()) {
      throw std::out_of_range("Bound exceeded in bounded int.");
    }
    return val_;
  }

  BoundedInt &operator++() {
    val_++;
    return *this;
  }

  BoundedInt operator++(int) {
    BoundedInt tmp = *this;
    ++(*this);
    return tmp;
  }

  BoundedInt operator+(int v) {
    BoundedInt other = *this;
    other.val_ += v;
    return other;
  }

  friend bool operator==(const BoundedInt &LHS, const BoundedInt &RHS) {
    return LHS.val_ == RHS.val_ && RHS.min_ == LHS.min_ && RHS.max_ == LHS.max_;
  }

  friend bool operator!=(const BoundedInt &LHS, const BoundedInt &RHS) {
    return !(RHS == LHS);
  }

  inline bool ExceedBound() const { return val_ > max_ || val_ < min_; }

  inline bool IsMax() const { return val_ == max_; }

  inline bool IsMin() const { return val_ == min_; }

 private:
  int val_;
  int max_;
  int min_;
};

}  // namespace util
