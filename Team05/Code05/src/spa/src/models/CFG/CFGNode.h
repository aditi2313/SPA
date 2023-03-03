#pragma once

#include <cassert>
#include <memory>
#include <vector>

namespace cfg {
class CFGNode;
class CFG;

typedef int CFGNodeId;
const CFGNodeId kEmptyId = -1;
const int kInvalidLine = -1;

class CFGNode {
 public:
  inline bool HasFirstChild() { return first_child_ != kEmptyId; }
  inline bool HasSecondChild() { return second_child_ != kEmptyId; }
  inline bool is_end() { return !HasFirstChild() && !HasSecondChild(); }
  inline bool is_empty() const {
    return start_line_ == kInvalidLine || end_line_ == kInvalidLine;
  }
  inline std::vector<int>& get_lines() {
    if (lines_.size() != 0) {
      return lines_;
    }
    if (is_empty()) return lines_;
    lines_.assign(end_line_ - start_line_ + 1, 0);

    for (int i = start_line_, j = 0; i <= end_line_; ++i, ++j) {
      lines_[j] = i;
    }
    return lines_;
  }

  friend bool operator==(const CFGNode& LHS, const CFGNode& RHS) {
    return LHS.id_ == RHS.id_ && LHS.end_line_ == RHS.end_line_ &&
           LHS.start_line_ == RHS.start_line_;
  }

  CFGNode& GetFirstChild();
  CFGNode& GetSecondChild();

 private:
  explicit CFGNode(int id, CFG* cfg) : id_(id), cfg_(cfg) {}
  CFGNode(int start, int end, int id, CFG* cfg)
      : cfg_(cfg), id_(id), start_line_(start), end_line_(end) {
    assert(end >= start);
  }
  void add_child(CFGNode& child) {
    if (first_child_ == kEmptyId) {
      first_child_ = child.id_;
      return;
    }
    assert(second_child_ == kEmptyId);
    second_child_ = child.id_;
  }
  int get_first_child() { return first_child_; }
  int get_second_child() { return second_child_; }
  int id_;
  std::vector<int> lines_;
  int start_line_ = kInvalidLine;
  int end_line_ = kInvalidLine;
  CFGNodeId first_child_ = kEmptyId;
  CFGNodeId second_child_ = kEmptyId;
  CFG* cfg_;
  friend class CFG;
};

}  // namespace cfg
