#pragma once

#include <memory>
#include <unordered_set>
#include <string>
#include <utility>
#include <vector>

#include "SP/visitors/TNodeVisitor.h"

namespace sp {
class VarCollector : public TNodeVisitor {
 public:
  void VisitVar(ast::VarNode* var_node) override;  

  std::unordered_set<std::string> get_vars() { return vars; }
  

 private:
  std::unordered_set<std::string> vars;
};
}  // namespace sp
