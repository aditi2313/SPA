#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

#include "CFGNode.h"

namespace cfg {

// class representing a CFG.
// Responsible for managing the nodes in memory.
class CFG {
 public:
  CFG() { root_ = std::make_shared<CFGNode>(); }

  CFGNodePtr AddChild(CFGNodePtr& parent, std::vector<int>& lines) {
    Manage(parent);
    CFGNodePtr node = std::make_unique<CFGNode>(lines);
    Manage(node);
    parent->add_child(node);
    node->add_parent(parent);
    return node;
  }

  CFGNodePtr AddChild(CFGNodePtr& parent, CFGNodePtr& child) {
    Manage(parent);
    Manage(child);
    parent->add_child(child);
    return child;
  }

  CFGNodePtr get_root() { return root_; }

 private:
  inline void Manage(CFGNodePtr node) { nodes_.insert(node); }
  std::unordered_set<CFGNodePtr> nodes_;
  CFGNodePtr root_;
};
}  // namespace cfg
