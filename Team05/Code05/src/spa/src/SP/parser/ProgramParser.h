#pragma once

#include <memory>

#include "SP/Lexer.h"
#include "Parser.h"
#include "models/AST/ProgramNode.h"

namespace sp {
class ProgramParser : Parser<ast::ProgramNode> {
 public:
  std::unique_ptr<ast::ProgramNode> parse(Lexer&) override;
  
  int get_and_increment_ctr() { return ctr++; }

 private:
  int ctr = 1;
};

}  // namespace sp
