#pragma once

#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class ExpressionVisitor : public TNodeVisitor {
 public:
  void VisitVar(ast::VarNode* var_node) override;

  void VisitPlus(ast::PlusNode* plus_node) override;

  void VisitMinus(ast::MinusNode* minus_node) override;

  void VisitTimes(ast::TimesNode* times_node) override;

  void VisitDiv(ast::DivNode* div_node) override;

  void VisitMod(ast::ModNode* mod_node) override;

  std::set<std::string> get_vars() { return vars; };

 private:
  std::set<std::string> vars;
};
}  // namespace sp