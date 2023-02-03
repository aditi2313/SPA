#include "ProgramNode.h"

namespace ast {

void ProgramNode::add_proc(std::unique_ptr<ProcNode> proc) {
  procs_.push_back(std::move(proc));
}

}  // namespace ast
