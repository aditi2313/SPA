#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class CallParser : Parser<ast::CallNode> {
 public:
  std::unique_ptr<ast::CallNode> parse(Lexer&) override {

  }

};
}  // namespace sp
