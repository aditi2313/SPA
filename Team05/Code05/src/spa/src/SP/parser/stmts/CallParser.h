#pragma once

#include "SP/parser/Parser.h"
#include "models/AST/stmt_node/StmtNode.h
#include "SP/parser/ProgramParser.h"
#include "models/AST/factor_node/FactorNode.h"

namespace sp {
class CallParser : Parser<ast::CallNode> {
 public:
  std::unique_ptr<ast::CallNode> parse(Lexer& lxr) override {
    if (lxr.GetTok() != kTokIdent) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("call should be followed by a name");
    }

    std::string var_name = lexer_->get_ident();
    std::cout << "call " + lexer_->get_ident() + "\n";

    if (lxr.GetTok() != kTokSemicolon) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("expected end of a statement");
    }
    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::CallNode>(
        ast::CallNode(std::move(var_node), line));
  }
};
}  // namespace sp
