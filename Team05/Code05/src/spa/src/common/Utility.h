#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace util {

template <class Node, class Container = std::vector<Node>>
struct GraphSearch {
  /// <summary>
  /// Runs BFS with the given get_children, initial children.
  /// </summary>
  /// <typeparam name="Node">The type of the nodes to run bfs</typeparam>
  /// <typeparam name="Container">The container of nodes returned</typeparam>
  /// <param name="get_children">The function to return the container of
  /// nodes</param> <param name="intial_children">The initial container of
  /// children</param> <param name="add_result">The method to add results
  /// to. Returns true if nothing needs to be done. False if no more children
  /// should be generated from this</param>
  inline static void BFS(std::function<Container(Node &)> get_children,
                         const Container intial_children,
                         std::function<bool(const Node &)> add_result) {
    std::queue<Node> frontier;
    std::unordered_set<Node> visited;
    for (auto &node : intial_children) {
      frontier.push(node);
    }
    while (!frontier.empty()) {
      auto &c = frontier.front();
      frontier.pop();
      if (visited.count(c)) {
        continue;
      }
      visited.insert(c);
      if (!add_result(c)) {
        continue;
      }

      for (auto &v : get_children(c)) {
        frontier.push(v);
      }
    }
  }
};

/// <summary>
/// Utility function for checking the instance of a
/// object.
/// </summary>
/// <typeparam name="Base">The base class of the object.</typeparam>
/// <typeparam name="Derived">The possibly derived class of the
/// object.</typeparam> <param name="other">The object to check</param>
/// <returns></returns>
template <class Derived, class Base>
inline bool InstanceOf(const Base &object) {
  return dynamic_cast<const Derived *>(&object) != nullptr;
}

/// <summary>
/// Utility function for comparing between two vectors of
/// unique pointers
/// </summary>
/// <returns>True if the two vectors are the same size and
/// the object each pointer is pointing to compares equal</returns>
template <class UniquePointerLHS, class UniquePointerRHS>
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
