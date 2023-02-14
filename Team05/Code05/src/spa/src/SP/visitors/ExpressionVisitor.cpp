#include "ExpressionVisitor.h"

namespace sp {
void ExpressionVisitor::VisitVar(ast::VarNode* var_node) {
  vars.insert(var_node->get_name());
}

void ExpressionVisitor::VisitPlus(ast::PlusNode* plus_node) {

}

void ExpressionVisitor::VisitMinus(ast::MinusNode* minus_node) {

}

void ExpressionVisitor::VisitTimes(ast::TimesNode* times_node) {

}

void ExpressionVisitor::VisitDiv(ast::DivNode* div_node) {

}

void ExpressionVisitor::VisitMod(ast::ModNode* mod_node) {

}
}