#pragma once

#include <memory>
#include <utility>

#include "SP/parser/Parser.h"
#include "SP/parser/relations/CondExprParser.h"
#include "SP/parser/stmts/StatementListParser.h"
#include "common/exceptions/SPExceptions.h"
#include "models/AST/Export.h"

namespace sp {
class IfParser : public Parser<ast::IfNode> {
 public:
  std::unique_ptr<ast::IfNode> parse(Lexer& lxr) override;
};
}  // namespace sp
