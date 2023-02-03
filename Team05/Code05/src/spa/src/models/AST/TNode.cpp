#include "TNode.h"

namespace ast {

	void ProgramNode::add_proc(std::unique_ptr<ProcNode> proc) {
		procs_.push_back(std::move(proc));
	}

	void StmtLstNode::add_stmt(std::unique_ptr<StatementNode> stmt) {
		stmts_.push_back(std::move(stmt));
	};

}  // namespace ast
