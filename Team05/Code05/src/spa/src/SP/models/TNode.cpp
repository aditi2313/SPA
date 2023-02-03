#include "SP/models/TNode.h"

namespace ast {

	VarNode::VarNode(std::string varName) : varName(varName) {};

	ConstNode::ConstNode(int val) : val(val) {};

	AssignNode::AssignNode() {};

	BinOpNode::BinOpNode(std::string opName) : opName(opName) {};

	ProcNode::ProcNode(std::string procName) : procName(procName) {};

	CallNode::CallNode() {};

	ReadNode::ReadNode() {};

	PrintNode::PrintNode() {};
	
	WhileNode::WhileNode() {};

	IfNode::IfNode() {};

	StmtLstNode::StmtLstNode() {};

}  // namespace ast
