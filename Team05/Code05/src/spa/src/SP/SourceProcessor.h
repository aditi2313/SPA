#include "../models/AST/factor_node/FactorNode.h"
#include "Lexer.h"
#include "SP/parser/ProgramParser.h"
#include "SP/visitors/AssignVisitor.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "models/AST/ProgramNode.h"
#include "parser/expression/ExpressionParser.h"
#include <memory>
#include <string>
#include <utility>

namespace sp {

// Facade class that serves as entry point for other components
class SourceProcessor {
 public:
  static std::unique_ptr<ast::ExprNode> CreateAstExpression(std::string expr) {
    sp::Lexer lxr(std::move(expr));
    sp::ExpressionParser exp_parser;
    return exp_parser.parse(lxr);
  }

  static std::unique_ptr<ast::ProgramNode> ParseProgram(std::string program) {
    sp::Lexer lxr(std::move(program));
    sp::ProgramParser program_parser;
    return program_parser.parse(lxr);
  }

};
}  // namespace sp
