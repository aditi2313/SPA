#include "ModifiesVisitor.h"

#include <memory>
#include <utility>
#include <unordered_set>

namespace sp {

void ModifiesVisitor::VisitAssign(ast::AssignNode* assign_node) {
  std::unordered_set<std::string> vars = {assign_node->get_var()->get_name()};
  pkb_ptr_->AddModifiesData(assign_node->get_line(), vars);
}

void ModifiesVisitor::VisitRead(ast::ReadNode* read_node) {
  std::unordered_set<std::string> vars = {read_node->get_var()->get_name()};
  pkb_ptr_->AddModifiesData(read_node->get_line(), vars);
}

}  // namespace sp
