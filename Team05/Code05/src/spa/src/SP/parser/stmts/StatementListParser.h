#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/Export.h"

namespace sp {
class StatementListParser : Parser<ast::StmtLstNode> {
 public:
  std::unique_ptr<ast::StmtLstNode> parse(Lexer&) override;
};
}  // namespace sp
