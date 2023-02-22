#pragma once

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
  inline void add_line(int line) { lines_.push_back(line); }

  inline bool HasFirstChild() { return children_.size() >= 1; }
  inline bool HasSecondChild() { return children_.size() >= 2; }
  inline bool is_end() { return children_.empty(); }

  friend bool operator==(const CFGNode& LHS, const CFGNode& RHS) {
    return LHS.id_ == RHS.id_;
  }

 private:
  CFGNode(int id) : id_(id) {}
  CFGNode(std::vector<int>& lines, int id) : id_(id) { lines_ = lines; }
  void add_child(CFGNode& child) { children_.push_back(child.id_); }
  int get_first_child() { return children_[0]; }
  int get_second_child() { return children_[1]; }
  std::vector<int> children_;
  std::vector<int> lines_;
  int id_;
  friend class CFG;
};

}  // namespace cfg
