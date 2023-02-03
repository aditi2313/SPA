#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "models/AST/stmt_node/StmtNode.h"

namespace ast {
class TNode {
 public:
  virtual void accept_visitor() = 0;
};

class ProgramNode : public TNode {  // root node
 public:
  explicit ProgramNode(std::unique_ptr<ProcNode> proc) {
    procs_.push_back(std::move(proc));
  }
  void add_proc(std::unique_ptr<ProcNode> proc);

 private:
  std::vector<std::unique_ptr<ProcNode>> procs_;
};

class ProcNode : public TNode {
 public:
  explicit ProcNode(std::string proc_name,
                    std::unique_ptr<StmtLstNode> stmt_lst)
      : proc_name_(proc_name) {
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
}  // namespace ast
