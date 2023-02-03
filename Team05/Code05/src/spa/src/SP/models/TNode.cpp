#include "SP/models/TNode.h"

namespace ast {

	VarNode::VarNode(std::string varName) : varName(varName) {};

	ConstNode::ConstNode(int val) : val(val) {};

	BinOpNode::BinOpNode(std::string opName) : opName(opName) {};

}  // namespace ast
