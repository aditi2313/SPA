#pragma once

#include "SP/parser/Parser.h"
#include "SP/parser/ProgramParser.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class ReadParser : Parser<ast::ReadNode> {
 public:
  explicit ReadParser(ProgramParser* parent) { parent_ = parent; }
  std::unique_ptr<ast::ReadNode> parse(Lexer& lxr) override {
    if (lxr.GetTok() != kTokIdent) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("read should be followed by a name");
    }

    std::string var_name = lxr.get_ident();
    std::cout << "read " + lxr.get_ident() + "\n";

    if (lxr.GetTok() != kTokSemicolon) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("expected end of a statement");
    }

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::ReadNode>(
        ast::ReadNode(std::move(var_node), parent_->get_and_increment_ctr()));
  }

 private:
  ProgramParser* parent_;
};
}  // namespace sp