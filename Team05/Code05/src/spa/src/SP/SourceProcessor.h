#include <string>
#include <memory>
#include "../models/AST/factor_node/FactorNode.h"
#include "Lexer.h"
#include "parser/expression/ExpressionParser.h"

namespace sp {

// Facade class that serves as entry point for other components
class SourceProcessor {
 public:
  static std::unique_ptr<ast::ExprNode> CreateAstExpression(std::string expr) {
    sp::Lexer lxr(expr);
    sp::ExpressionParser exp_parser;
    return exp_parser.parse(lxr);
  }
};
}  // namespace sp
