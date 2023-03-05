#pragma once

#include <cassert>
#include <memory>
#include <vector>

#include "common/Utiity.h"

namespace cfg {

class CFGNode;
class CFG;

typedef int CFGNodeId;
const CFGNodeId kEmptyId = -1;
const int kInvalidLine = -1;

class CFGNode {
 public:
  inline bool HasFirstChild() const { return first_child_ != kEmptyId; }
  inline bool HasSecondChild() const { return second_child_ != kEmptyId; }
  inline bool is_end() const { return !HasFirstChild() && !HasSecondChild(); }
  inline bool is_empty() const {
    return start_line_ == kInvalidLine || end_line_ == kInvalidLine;
  }
  inline std::vector<int>& get_lines() { return lines_; }

  inline util::BoundedInt back() {
    return util::BoundedInt(end_line_, end_line_, start_line_);
  }

  inline util::BoundedInt front() {
    return util::BoundedInt(start_line_, end_line_, start_line_);
  }

  friend bool operator==(const CFGNode& LHS, const CFGNode& RHS) {
    return LHS.id_ == RHS.id_ && LHS.end_line_ == RHS.end_line_ &&
           LHS.start_line_ == RHS.start_line_ &&
           LHS.first_child_ == RHS.first_child_ &&
           LHS.second_child_ == RHS.second_child_;
  }

  friend bool operator!=(const CFGNode& LHS, const CFGNode& RHS) {
    return !(LHS == RHS);
  }

 private:
  inline void InitialiseLines() {
    if (lines_.size() != 0) {
      return;
    }
    if (is_empty()) return;
    lines_.assign(end_line_ - start_line_ + 1, 0);

    for (int i = start_line_, j = 0; i <= end_line_; ++i, ++j) {
      lines_[j] = i;
    }
  }
  explicit CFGNode(int id, CFG& cfg) : id_(id), cfg_(cfg) {}
  CFGNode(int start, int end, int id, CFG& cfg)
      : cfg_(cfg), id_(id), start_line_(start), end_line_(end) {
    assert(end >= start);
    InitialiseLines();
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
  int get_first_child() const { return first_child_; }
  int get_second_child() const { return second_child_; }
  int id_;
  std::vector<int> lines_;
  int start_line_ = kInvalidLine;
  int end_line_ = kInvalidLine;
  CFGNodeId first_child_ = kEmptyId;
  CFGNodeId second_child_ = kEmptyId;
  CFG& cfg_;
  friend class CFG;
};

}  // namespace cfg
