#include <vector>
#include <string>

namespace ast {
class TNode {
 public:
	 std::vector<TNode> children;

	 virtual void add_child(TNode node) {
		 children.push_back(node);
	 }

};

class VarNode : public TNode {
	std::string varName;
	explicit VarNode(std::string varName);

};

class ConstNode : public TNode {
	int val;
	explicit ConstNode(int val);
	
};

class AssignNode : public TNode {

};

class BinOpNode : public TNode {
	std::string opName;
	explicit BinOpNode(std::string opName);

};

class ProcedureNode : public TNode {
	std::string procName;
};

class CallNode : public TNode {

};

class ReadNode : public TNode {

};

class PrintNode : public TNode {

};

class WhileNode : public TNode {

};

class IfElseNode : public TNode {

};

class StmtLstNode : public TNode {

};

}  // namespace ast
