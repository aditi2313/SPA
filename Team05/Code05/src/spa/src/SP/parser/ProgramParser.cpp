#include "ProgramParser.h"

#include "ProcedureParser.h"
#include "SP/lexer/Lexer.h"

namespace sp {
std::unique_ptr<ast::ProgramNode> ProgramParser::parse(Lexer& lxr) {
  ProcedureParser proc_parser;
  lxr.GetTokAndIncrement();
  auto first_child = proc_parser.parse(lxr);
  auto root = std::make_unique<ast::ProgramNode>(std::move(first_child));
  // todo(gab) think of how to refactor
  // token and lxr #40
  int current_tok = lxr.GetTokAndIncrement();
  while (true) {
    if (current_tok == kTokEof) {
      break;
    } else if (current_tok == kTokProcedure) {
      root->add_proc(proc_parser.parse(lxr));
      current_tok = lxr.get_tok();
    } else {
      current_tok = lxr.GetTokAndIncrement();
    }
  }
  return std::move(root);
}

}  // namespace sp
