#include "StatementParser.h"

#include "AssignParser.h"
#include "CallParser.h"
#include "PrintParser.h"
#include "ReadParser.h"

namespace sp {
std::unique_ptr<ast::StmtNode> StatementParser::parse(Lexer& lxr) {
  ReadParser read_parser;
  PrintParser print_parser;
  CallParser call_parser;
  AssignParser assign_parser;
  auto tok = lxr.GetTok();
  lxr.Increment();
  switch (tok) {
    case kTokRead:
      return read_parser.parse(lxr);
    case kTokPrint:
      return print_parser.parse(lxr);
    case kTokCall:
      return call_parser.parse(lxr);
    case kTokWhile:
      return nullptr;
    case kTokIf:
      return nullptr;
    case kTokIdent:
      return assign_parser.parse(lxr);
    default:
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error(
          "expected a stmt (read | print | call "
          "| while | if | assign)");
  }
}
}  // namespace sp
