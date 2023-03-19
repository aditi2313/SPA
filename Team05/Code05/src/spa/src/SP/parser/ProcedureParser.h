#pragma once

#include <memory>

#include "SP/parser/Parser.h"
#include "models/AST/Export.h"

namespace sp {
class ProcedureParser : Parser<ast::ProcNode> {
 public:
  std::unique_ptr<ast::ProcNode> parse(Lexer&) override;
};

}  // namespace sp
