#include "FactorParser.h"
#include "common/exceptions/SP.h"

namespace sp {
std::unique_ptr<ast::FactorNode> FactorParser::parse(Lexer &lxr) {
  auto tok = lxr.get_tok();

  if (tok == Token::kTokIdent) {
    return std::make_unique<ast::VarNode>(ast::VarNode(lxr.get_ident()));
  } else if (tok == Token::kTokInteger) {
    return std::make_unique<ast::ConstNode>(ast::ConstNode(lxr.get_integer()));
  } else {  // TODO(aizatazhar): parse '(' expr ')'
    throw ParseFactorSyntaxException("Expected variable, constant or expr");
  }
}
}  // namespace sp
