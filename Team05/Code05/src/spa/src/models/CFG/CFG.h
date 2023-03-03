#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>

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

  /// <summary>
  /// Adds the given code block starting from the
  /// start line to the end line to the cfg. [start_line, end_line]
  /// </summary>
  /// <param name="parent">The parent cfg block</param>
  /// <param name="start_line">The starting line for
  /// the cfg block</param>
  /// <param name="end_line">The ending line for the cfg block</param>
  /// <returns></returns>
  CFGNode& AddChild(CFGNode& parent, int start_line, int end_line);

  CFGNode& AddChild(CFGNode& parent, CFGNode& child) {
    parent.add_child(child);
    return child;
  }
  CFGNode& GetFirstChild(CFGNode& node);
  CFGNode& GetSecondChild(CFGNode& node);

  CFGNode& get_root() { return nodes_[0]; }

 private:
  CFGNode& get_node_from_id(int id) {
    int index = id_to_indexes_.at(id);
    return nodes_[index];
  }
  std::deque<CFGNode> nodes_;
  std::unordered_map<CFGNodeId, int> id_to_indexes_;
  ProgramCFG* program_;
};
}  // namespace cfg
