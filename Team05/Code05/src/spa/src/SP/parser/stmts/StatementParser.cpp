#include "StatementParser.h"

#include "AssignParser.h"
#include "CallParser.h"
#include "PrintParser.h"
#include "ReadParser.h"

namespace sp {
std::unique_ptr<ast::StmtNode> StatementParser::parse(Lexer& lxr) {
  ReadParser read_parser(this->parent_);
  PrintParser print_parser(this->parent_);
  CallParser call_parser(this->parent_);
  AssignParser assign_parser(this->parent_);
  switch (prev_token_) {
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