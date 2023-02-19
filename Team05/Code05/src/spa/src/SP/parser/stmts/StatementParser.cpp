#include "StatementParser.h"

#include "AssignParser.h"
#include "CallParser.h"
#include "IfParser.h"
#include "PrintParser.h"
#include "ReadParser.h"
#include "WhileParser.h"

namespace sp {
std::unique_ptr<ast::StmtNode> StatementParser::parse(Lexer& lxr) {
  ReadParser read_parser;
  PrintParser print_parser;
  CallParser call_parser;
  AssignParser assign_parser;
  IfParser if_parser;
  WhileParser while_parser;

  auto tok = lxr.get_tok();
  switch (tok) {
    case Token::kTokRead:
      return read_parser.parse(lxr);
    case Token::kTokPrint:
      return print_parser.parse(lxr);
    case Token::kTokCall:
      return call_parser.parse(lxr);
    case Token::kTokWhile:
      return while_parser.parse(lxr);
    case Token::kTokIf:
      return if_parser.parse(lxr);
    case Token::kTokIdent:
      return assign_parser.parse(lxr);
    default:
      throw ParseStmtSyntaxException("expected a stmt (read | print | call "
                                   "| while | if | assign)");
  }
}
}  // namespace sp
