#pragma once

#include <memory>
#include <utility>

#include "Parser.h"
#include "SP/lexer/Lexer.h"
#include "models/AST/ProgramNode.h"

namespace sp {
class ProgramParser : Parser<ast::ProgramNode> {
 public:
  std::unique_ptr<ast::ProgramNode> parse(Lexer&) override;
};

}  // namespace sp
