#pragma once

#include <deque>
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

  /// <summary>
  /// Utility function for adding a node to the cfg without
  /// requiring a parent.
  /// </summary>
  /// <param name="start_line">The start line of the cfg node</param>
  /// <param name="end_line">The end line of the cfg node</param>
  /// <returns></returns>
  CFGNode& AddNode(int start_line, int end_line);

  /// <summary>
  /// Adds an empty node.
  /// </summary>
  /// <returns></returns>
  CFGNode& AddNode();

  CFGNode& AddChild(CFGNode& parent, CFGNode& child) {
    parent.add_child(child);
    return child;
  }
  CFGNode& GetFirstChild(CFGNode& node);
  CFGNode& GetSecondChild(CFGNode& node);

  CFGNode& get_root() { return nodes_[0]; }

  /// <summary>
  /// Function for obtaining the non empty children of the provided
  /// node. If the child of this node is empty,
  /// we will traverse the first child of the empty node.
  /// This is under the assumption that if a node is empty, it can only
  /// have one child. This is because if-nodes and while nodes
  /// are the only nodes with two children, and they are guaranteed
  /// to be non-empty.
  ///
  /// </summary>
  /// <param name="node">The node of which we are obtaining the
  /// children.</param> <returns></returns>
  std::vector<CFGNode*> GetNonEmptyChildren(CFGNode& node) {
    if (node.is_empty()) {
      return GetNonEmptyChildren(GetFirstChild(node));
    }
    std::vector<CFGNode*> result;
    if (node.HasFirstChild()) {
      auto& curr = GetFirstChild(node);
      while (curr.is_empty()) {
        curr = GetFirstChild(curr);
      }
      result.push_back(&curr);
    }

    if (node.HasSecondChild()) {
      auto& curr = GetSecondChild(node);
      while (curr.is_empty()) {
        curr = GetFirstChild(curr);
      }
      result.push_back(&curr);
    }
    return result;
  }

  friend bool operator==(const CFG& LHS, const CFG& RHS) {
    return LHS.id_to_indexes_ == RHS.id_to_indexes_ && LHS.nodes_ == RHS.nodes_;
  }

 private:
  CFGNode& get_node_from_id(CFGNodeId id) {
    int index = id_to_indexes_.at(id);
    return nodes_[index];
  }
  std::deque<CFGNode> nodes_;
  std::unordered_map<CFGNodeId, int> id_to_indexes_;
  ProgramCFG* program_;
};
}  // namespace cfg
