#include "CFGNode.h"
#include "CFG.h"

namespace cfg {
CFGNode& CFGNode::GetFirstChild() { return cfg_->GetFirstChild(*this); }
CFGNode& CFGNode::GetSecondChild() { return cfg_->GetSecondChild(*this); }
}  // namespace cfg
