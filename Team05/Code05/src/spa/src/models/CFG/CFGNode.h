#pragma once

#include <memory>
#include <vector>

namespace sp {
class CFGVisitor;
}

namespace cfg {
class CFGNode;

typedef std::shared_ptr<CFGNode> CFGNodePtr;
typedef std::weak_ptr<CFGNode> CFGNodeWeakPtr;

class CFGNode {
 public:
  CFGNode() {}

  CFGNode(std::vector<int>& lines) { lines_ = lines; }

  inline void add_line(int line) { lines_.push_back(line); }

  CFGNodeWeakPtr get_first_child() { return children_[0]; }
  CFGNodeWeakPtr get_second_child() { return children_[1]; }
  inline bool HasFirstChild() { return children_.size() >= 1; }
  inline bool HasSecondChild() { return children_.size() >= 2; }
  inline bool is_end() { return children_.empty(); }

 private:
  void add_child(const CFGNodePtr& child) {
    children_.push_back(CFGNodeWeakPtr(child));
  }

  void add_parent(const CFGNodePtr& parent) {
    parent_.push_back(CFGNodeWeakPtr(parent));
  }
  std::vector<CFGNodeWeakPtr> parent_;
  std::vector<CFGNodeWeakPtr> children_;
  std::vector<int> lines_;
  friend class CFG;
};

}  // namespace cfg
