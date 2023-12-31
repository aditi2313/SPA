#include "CFG.h"

#include "ProgramCFG.h"

namespace cfg {

CFG::CFG(ProgramCFG* program) {
  program_ = program;
  AddNode();
}

CFGNode& CFG::AddChild(CFGNode& parent, int start_line, int end_line) {
  auto& child = AddNode(start_line, end_line);
  parent.add_child(child);
  return child;
}

CFGNode& CFG::AddNode() {
  int id = program_->GetAndIncrementId();
  id_to_indexes_[id] = nodes_.size();
  nodes_.push_back(CFGNode(id, *this));
  return get_node_from_id(id);
}

CFGNode& CFG::AddNode(int start_line, int end_line) {
  int id = program_->GetAndIncrementId();
  id_to_indexes_[id] = nodes_.size();
  nodes_.push_back(CFGNode(start_line, end_line, id, *this));
  if (start_line == kInvalidLine && end_line == kInvalidLine)
    return get_node_from_id(id);
  CFGNode* node = &get_node_from_id(id);
  for (int i = start_line; i <= end_line; ++i) {
    program_->AddLineToCfg(i, node);
  }
  return *node;
}

CFGNode& CFG::GetFirstChild(CFGNode& node) {
  return get_node_from_id(node.get_first_child());
}

CFGNode& CFG::GetSecondChild(CFGNode& node) {
  return get_node_from_id(node.get_second_child());
}

}  // namespace cfg
