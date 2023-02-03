#include <vector>
#include <string>
#include <memory>

namespace ast {
class TNode {
 public:

	 virtual void accept_visitor() = 0;

};

class ProgramNode : public TNode { //root node
public:
	explicit ProgramNode(std::unique_ptr<ProcNode> proc) {
		procs_.push_back(std::move(proc));
	}
	void add_proc(std::unique_ptr<ProcNode> proc);
private:
	std::vector<std::unique_ptr<ProcNode>> procs_;
};

class ProcNode : public TNode { //stmtlst children, parent is always root
public:
	explicit ProcNode(std::string proc_name, std::unique_ptr<StmtLstNode> stmt_lst) : proc_name_(proc_name) {
		stmt_lst_ = std::move(stmt_lst);
	}
private:
	std::string proc_name_;
	std::unique_ptr<StmtLstNode> stmt_lst_;
};

class StmtLstNode : public TNode {
public:
	explicit StmtLstNode(std::unique_ptr<StatementNode> stmt) {
		stmts_.push_back(std::move(stmt));
	}
	void add_stmt(std::unique_ptr<StatementNode> stmt);

private:
	std::vector<std::unique_ptr<StatementNode>> stmts_;
};

class FactorNode : public TNode {

};

class ExprNode : public FactorNode {

};

class TermNode : public ExprNode {

};

class VarNode : public FactorNode { //cannot have children
 public:
	explicit VarNode(std::string varName);

private:
	std::string varName;
};

class ConstNode : public FactorNode { //cannot have children
 public:
	explicit ConstNode(int val);
 private:
	 int val_;
};

class PlusNode : public ExprNode {
public:
	explicit PlusNode(std::unique_ptr<ExprNode> expr, std::unique_ptr<TermNode> term) {
		expr_ = std::move(expr);
		term_ = std::move(term);
	}
private:
	std::unique_ptr<ExprNode> expr_;
	std::unique_ptr<TermNode> term_;
};

class MinusNode : public ExprNode {
public:
	explicit MinusNode(std::unique_ptr<ExprNode> expr, std::unique_ptr<TermNode> term) {
		expr_ = std::move(expr);
		term_ = std::move(term);
	}
private:
	std::unique_ptr<ExprNode> expr_;
	std::unique_ptr<TermNode> term_;
};

class TimesNode : public TermNode {
public:
	explicit TimesNode(std::unique_ptr<TermNode> term, std::unique_ptr<FactorNode> factor) {
		term_ = std::move(term);
		factor_ = std::move(factor);
	}
private:
	std::unique_ptr<TermNode> term_;
	std::unique_ptr<FactorNode> factor_;
};

class DivNode : public TermNode {
public:
	explicit DivNode(std::unique_ptr<TermNode> term, std::unique_ptr<FactorNode> factor) {
		term_ = std::move(term);
		factor_ = std::move(factor);
	}
private:
	std::unique_ptr<TermNode> term_;
	std::unique_ptr<FactorNode> factor_;
};

class ModNode : public TermNode {
public:
	explicit ModNode(std::unique_ptr<TermNode> term, std::unique_ptr<FactorNode> factor) {
		term_ = std::move(term);
		factor_ = std::move(factor);
	}
private:
	std::unique_ptr<TermNode> term_;
	std::unique_ptr<FactorNode> factor_;
};

class StatementNode : public TNode {

};

class AssignNode : public StatementNode { //needs strictly one left (var only) and one right child (const or var or binop)
public:
	explicit AssignNode(std::unique_ptr<VarNode> var, std::unique_ptr<ExprNode> exp) {
		var_ = std::move(var);
		exp_ = std::move(exp);
	}
private:
	std::unique_ptr<VarNode> var_;
	std::unique_ptr<ExprNode> exp_;
};

class ReadNode : public StatementNode {
public:
	explicit ReadNode(std::unique_ptr<VarNode> var) {
		var_ = std::move(var);
	}
private:
	std::unique_ptr<VarNode> var_;
};

class PrintNode : public StatementNode {
public:
	explicit PrintNode(std::unique_ptr<VarNode> var) {
		var_ = std::move(var);
	}
private:
	std::unique_ptr<VarNode> var_;
};
}  // namespace ast
