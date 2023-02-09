#pragma once
#include <memory>
#include <string>
#include <utility>

#include "models/AST/StmtLstNode.h"
#include "models/AST/TNode.h"

namespace ast {
class ProcNode : public TNode {
 public:
  explicit ProcNode(std::string proc_name,
                    std::unique_ptr<StmtLstNode> stmt_lst)
      : proc_name_(proc_name) {
    stmt_lst_ = std::move(stmt_lst);
  }

  inline std::unique_ptr<StmtLstNode>& get_children() { return stmt_lst_; }

  inline std::string get_name() { return proc_name_; }

  void AcceptVisitor(sp::TNodeVisitor* visitor) override;
  void AcceptVisitor(sp::ValidatorVisitor* visitor);

 private:
  std::string proc_name_;
  std::unique_ptr<StmtLstNode> stmt_lst_;
};
}  // namespace ast
