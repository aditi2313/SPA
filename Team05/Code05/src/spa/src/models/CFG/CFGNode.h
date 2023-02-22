#pragma once

#include <cassert>
#include <memory>
#include <vector>

namespace sp {
class CFGVisitor;
}

namespace cfg {
class CFGNode;

typedef std::unique_ptr<CFGNode> CFGNodePtr;

class CFGNode {
 public:
  inline bool HasFirstChild() { return children_.size() >= 1; }
  inline bool HasSecondChild() { return children_.size() >= 2; }
  inline bool is_end() { return children_.empty(); }
  inline bool is_empty() { return start_line_ == -1 || end_line_ == -1; }
  inline std::vector<int> get_lines() {
    if (is_empty()) return std::vector<int>(0, 0);
    std::vector<int> result(end_line_ - start_line_ + 1, 0);
    for (int i = start_line_, j = 0; i <= end_line_; ++i, ++j) {
      result[j] = i;
    }
    return result;
  }

  friend bool operator==(const CFGNode& LHS, const CFGNode& RHS) {
    return LHS.id_ == RHS.id_ && LHS.end_line_ == RHS.end_line_ &&
           LHS.start_line_ == RHS.start_line_;
  }

 private:
  explicit CFGNode(int id) : id_(id) {}
  CFGNode(int start, int end, int id)
      : id_(id), start_line_(start), end_line_(end) {
    assert(end >= start);
  }
  void add_child(CFGNode& child) { children_.push_back(child.id_); }
  int get_first_child() { return children_[0]; }
  int get_second_child() { return children_[1]; }
  std::vector<int> children_;
  int id_;
  int start_line_ = -1;
  int end_line_ = -1;
  friend class CFG;
};

}  // namespace cfg
