#include "ProgramParser.h"

#include "ProcedureParser.h"

namespace sp {
std::unique_ptr<ast::ProgramNode> ProgramParser::parse(Lexer& lxr) {
  ProcedureParser proc_parser(this);
  auto first_child = proc_parser.parse(lxr);
  auto root = std::make_unique < ast::ProgramNode(std::move(first_child));
  // todo(gab) think of how to refactor
  // token and lxr
  int current_tok = lxr.GetTok();
  while (true) {
    if (current_tok == kTokEof) {
      break;
    } else if (current_tok == kTokProcedure) {
      root->add_proc(proc_parser.parse(lxr));
    } else {
      current_tok = lxr.GetTok();
    }
  }
  return std::move();
}

}  // namespace sp