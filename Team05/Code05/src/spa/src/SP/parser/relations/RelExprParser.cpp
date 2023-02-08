#include "RelExprParser.h"

#include "models/AST/Token.h"

namespace sp {

bool IsRelation(Token& token) { return token == Token::kTokEquals; }
std::unique_ptr<ast::RelExprNode> RelExprParser::parse(Lexer& lxr) {
  auto left_factor = rel_parser_.parse(lxr);
  auto middle = lxr.get_tok();

  /// Todo(Gab) add logic to verify that it is a relation
  /// If it is not -- return nullptr
  lxr.Increment();
  auto right_factor = rel_parser_.parse(lxr);

  // Todo(Gab) 
  return std::make_unique<ast::RelExprNode>(
      std::move(left_factor, right_factor));
}
}  // namespace sp
