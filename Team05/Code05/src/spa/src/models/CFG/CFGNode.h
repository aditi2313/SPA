#pragma once

#include <cassert>
#include <memory>
#include <vector>

namespace sp {
class CFGVisitor;
}

namespace cfg {
class CFGNode;

typedef int CFGNodeId;
const CFGNodeId kEmptyId = -1;
const int kInvalidLine = -1;

typedef std::unique_ptr<CFGNode> CFGNodePtr;

class CFGNode {
 public:
  inline bool HasFirstChild() { return first_child_ != kEmptyId; }
  inline bool HasSecondChild() { return second_child_ != kEmptyId; }
  inline bool is_end() { return !HasFirstChild() && !HasSecondChild(); }
  inline bool is_empty() {
    return start_line_ == kInvalidLine || end_line_ == kInvalidLine;
  }
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

  friend bool operator!=(const CFGNode& LHS, const CFGNode& RHS) {
    return !(LHS == RHS);
  }

 private:
  explicit CFGNode(int id) : id_(id) {}
  CFGNode(int start, int end, int id)
      : id_(id), start_line_(start), end_line_(end) {
    assert(end >= start);
  }
  void add_child(CFGNode& child) {
    if (first_child_ == kEmptyId) {
      first_child_ = child.id_;
      return;
    }
    assert(second_child_ == kEmptyId);
    assert(!is_empty());
    second_child_ = child.id_;
  }
  int get_first_child() { return first_child_; }
  int get_second_child() { return second_child_; }
  int id_;
  int start_line_ = kInvalidLine;
  int end_line_ = kInvalidLine;
  CFGNodeId first_child_ = kEmptyId;
  CFGNodeId second_child_ = kEmptyId;
  friend class CFG;
};

}  // namespace cfg
