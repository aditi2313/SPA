#include "ProgramValidator.h"
#include "ProcedureValidator.h"
#include "CallValidator.h"

namespace sp {
    bool ProgramValidator::Validate() {
        // Traverse tree to get required info
        root_->AcceptVisitor(this);
        auto procedure_validator = sp::ProcedureValidator(procedure_names_);
        auto call_validator = sp::CallValidator(procedure_names_, call_names_);
        return procedure_validator.Validate() && call_validator.Validate();
    }

    void ProgramValidator::Visit(ast::ProgramNode *program_node) {
        auto proc_nodes = std::move(program_node->get_children());
        for (auto &proc_node : proc_nodes) {
            proc_node->AcceptVisitor(this);
        }
    }

    void ProgramValidator::Visit(ast::ProcNode *proc_node) {
        auto proc_name = proc_node->get_name();
        procedure_names_.push_back(proc_name);

        auto stmtlst_node = std::move(proc_node->get_children());
        stmtlst_node->AcceptVisitor(this);
    }

    void ProgramValidator::Visit(ast::StmtLstNode *stmtlst_node) {
        for (auto &stmt_node : stmtlst_node->get_children()) {
            stmt_node->AcceptVisitor(this);
        }
    }

    void ProgramValidator::Visit(ast::ReadNode *read_node) { }

    void ProgramValidator::Visit(ast::PrintNode *print_node) { }

    void ProgramValidator::Visit(ast::CallNode *call_node) {
        auto proc_name = call_node->get_var()->get_name();
        call_names_.push_back(proc_name);
    }

    void ProgramValidator::Visit(ast::AssignNode *assign_node) { }
}  // namespace sp
