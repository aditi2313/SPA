#include "VarCollector.h"

namespace sp {
void VarCollector::VisitVar(ast::VarNode* var_node) {
  vars.insert(var_node->get_name());
}

void VarCollector::VisitPlus(ast::PlusNode* plus_node) {
  plus_node->get_expr()->AcceptVisitor(this);
  plus_node->get_term()->AcceptVisitor(this);
}

void VarCollector::VisitMinus(ast::MinusNode* minus_node) {
  minus_node->get_expr()->AcceptVisitor(this);
  minus_node->get_term()->AcceptVisitor(this);
}

void VarCollector::VisitTimes(ast::TimesNode* times_node) {
  times_node->get_factor()->AcceptVisitor(this);
  times_node->get_term()->AcceptVisitor(this);
}

void VarCollector::VisitDiv(ast::DivNode* div_node) {
  div_node->get_factor()->AcceptVisitor(this);
  div_node->get_term()->AcceptVisitor(this);
}

void VarCollector::VisitMod(ast::ModNode* mod_node) {
  mod_node->get_factor()->AcceptVisitor(this);
  mod_node->get_term()->AcceptVisitor(this);
}
}  // namespace sp
