#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class PrintParser : Parser<ast::PrintNode> {
 public:
  std::unique_ptr<ast::PrintNode> parse(Lexer& lxr) override {
    if (lxr.GetTok() != kTokIdent) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("print should be followed by a name");
    }

    std::string var_name = lexer_->get_ident();
    std::cout << "print " + lexer_->get_ident() + "\n";

    if (lxr.GetTok() != kTokSemicolon) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("expected end of a statement");
    }

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::PrintNode>(
        ast::PrintNode(std::move(var_node), lxr.get_and_increment_stmtctr()));
  }
};
}  // namespace sp
