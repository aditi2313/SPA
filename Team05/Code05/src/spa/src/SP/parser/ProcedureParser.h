#pragma once

#include <memory>

#include "Lexer.h"
#include "models/AST/ProcNode.h"

namespace sp {
class ProcedureParser : Parser<ast::ProcNode> {
 public:
  ProcedureParser(ProgramParser* parent) { this->parent = parent; }
  std::unique_ptr<ast::ProcNode> parse(Lexer&) override;

 private:
  ProgramParser* parent_;
};

}  // namespace sp
