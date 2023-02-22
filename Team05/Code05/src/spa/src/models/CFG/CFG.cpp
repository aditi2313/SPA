#include "CFG.h"

#include "ProgramCFG.h"

namespace cfg {

CFG::CFG(ProgramCFG* program) {
  program_ = program;
  std::vector<int> lines{};
  nodes_.push_back(CFGNode(lines, program->GetAndIncrementId()));
}

CFGNode& CFG::AddChild(CFGNode& parent, std::vector<int>& lines) {
  int id = program_->GetAndIncrementId();
  id_to_indexes_[id] = nodes_.size();
  nodes_.push_back(CFGNode(lines, id));
  parent.add_child(nodes_[id]);
  return nodes_[id];
}

CFGNode& CFG::GetFirstChild(CFGNode& node) {
  return get_node_from_id(node.get_first_child());
}

CFGNode& CFG::GetSecondChild(CFGNode& node) {
  return get_node_from_id(node.get_second_child());
}

}  // namespace cfg