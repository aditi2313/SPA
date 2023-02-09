#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <unordered_set>

#include "models/AST/ProgramNode.h"
#include "Validator.h"
#include "ValidatorVisitor.h"

namespace sp {
class ProgramValidator : public Validator, ValidatorVisitor {
 public:
    explicit ProgramValidator(std::unique_ptr<ast::ProgramNode> &root)
        : root_(root) { }

    bool Validate() override;

    void Visit(ast::ProgramNode* program_node) override;
    void Visit(ast::ProcNode* proc_node) override;
    void Visit(ast::ReadNode* proc_node) override;
    void Visit(ast::PrintNode* proc_node) override;
    void Visit(ast::CallNode* proc_node) override;
    void Visit(ast::AssignNode* proc_node) override;

 private:
    std::unique_ptr<ast::ProgramNode> &root_;
    std::vector<std::string> procedure_names_;
    std::vector<std::string> call_names_;
};
}  // namespace sp
