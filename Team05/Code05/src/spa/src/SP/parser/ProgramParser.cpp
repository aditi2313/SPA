#include "ProgramParser.h"

#include "ProcedureParser.h"
#include "SP/lexer/Lexer.h"

namespace sp {
std::unique_ptr<ast::ProgramNode> ProgramParser::parse(Lexer& lxr) {
  ProcedureParser proc_parser;
  lxr.GetTokAndIncrement();
  auto first_child = proc_parser.parse(lxr);
  auto root = std::make_unique<ast::ProgramNode>(std::move(first_child));

  Token current_tok = lxr.GetTokAndIncrement();
  while (current_tok != Token::kTokEof) {
    if (current_tok == Token::kTokProcedure) {
      root->add_proc(proc_parser.parse(lxr));
      current_tok = lxr.get_tok();
    } else {
      current_tok = lxr.GetTokAndIncrement();
    }
  }
  return std::move(root);
}

}  // namespace sp
