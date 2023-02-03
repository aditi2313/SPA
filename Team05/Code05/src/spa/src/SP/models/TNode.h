#include <vector>
#include <string>

namespace ast {
class TNode {
 public:
	 std::vector<TNode> children; //have to change to left right because of assignment

	 virtual void add_child(TNode node) { //change to pointer assignment
		 children.push_back(node); //shld be in cpp file, not header
	 }

};

class ProgramNode : public TNode { //root node

};

class VarNode : public TNode { //cannot have children
	std::string varName;
	explicit VarNode(std::string varName);

	void add_child(TNode node); //throw error
};

class ConstNode : public TNode { //cannot have children
	int val;
	explicit ConstNode(int val);

	void add_child(TNode node); //throw error
};

class AssignNode : public TNode { //needs strictly one left (var only) and one right child (const or var or binop)
	TNode left;
	TNode right;

	void add_left_child(TNode node);
	void add_right_child(TNode node); 
};

class BinOpNode : public TNode { //needs strictly one left and one right child, but not necessarily numbers or const
	std::string opName;
	TNode left;
	TNode right;
	explicit BinOpNode(std::string opName);

	void add_left_child(TNode node);
	void add_right_child(TNode node);

};

class ProcNode : public TNode { //stmtlst children, parent is always root
	std::string procName;
	explicit ProcNode(std::string procName);
};

class CallNode : public TNode { //no children
	std::string procName;
	void add_child(TNode node); //throw error
};

class ReadNode : public TNode { //val child
	TNode child;
	void add_child(TNode node);
};

class PrintNode : public TNode { //val child
	TNode child;
	void add_child(TNode node);
};

class WhileNode : public TNode { //condition and stmtlst children
	TNode condition; //ensure it is a bin op (either greater, lesser or equal)
	TNode stmtLst; //ensure it is a stmtlst
};

class IfNode : public TNode { //condition, then stmtlst, else stmtlst children
	TNode condition; //ensure it is a bin op
	TNode thenStmtLst;
	TNode elseStmtLst;
};

class StmtLstNode : public TNode {
	std::string name; //for else and then
};

}  // namespace ast
