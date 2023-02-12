#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/StmtLstNode.h"

namespace sp {
class StatementListParser : SelectClParser<ast::StmtLstNode> {
 public:
  std::unique_ptr<ast::StmtLstNode> parse(Lexer&);
};
}  // namespace sp
