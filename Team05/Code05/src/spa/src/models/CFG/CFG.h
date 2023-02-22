#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CFGNode.h"

namespace cfg {
class ProgramCFG;  // Forward declaration for program cfg

// class representing a CFG.
// Responsible for managing the nodes in memory.
class CFG {
 public:
  explicit CFG(ProgramCFG* program);

  CFG() : program_(nullptr) {}

  bool IsEmpty() { return nodes_.size() == 0; }

  CFGNode& AddChild(CFGNode& parent, std::vector<int>& lines);

  CFGNode& AddChild(CFGNode& parent, CFGNode& child) {
    parent.add_child(child);
    return child;
  }
  CFGNode& GetFirstChild(CFGNode& node);
  CFGNode& GetSecondChild(CFGNode& node);

  const CFGNode& get_root() { return nodes_[0]; }

 private:
  CFGNode& get_node_from_id(int id) {
    int index = id_to_indexes_.at(id);
    return nodes_[index];
  }
  std::vector<CFGNode> nodes_;
  std::unordered_map<int, int> id_to_indexes_;
  ProgramCFG* program_;
};
}  // namespace cfg
