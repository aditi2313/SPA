#pragma once

#include <memory>
#include <utility>

#include "SP/parser/Parser.h"
#include "SP/parser/relations/CondExprParser.h"
#include "SP/parser/stmts/StatementListParser.h"
#include "common/exceptions/SPExceptions.h"
#include "models/AST/Export.h"

namespace sp {
class WhileParser : public Parser<ast::WhileNode> {
 public:
  std::unique_ptr<ast::WhileNode> parse(Lexer& lxr) override {
    StatementListParser stmt_list_parser;
    CondExprParser cond_parser;
    int stmt = lxr.GetAndIncrementStmtCtr();
    AssertExpectedToken(ParseWhileSyntaxException::kParseWhileSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokWhile);

    AssertExpectedToken(ParseWhileSyntaxException::kParseWhileSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokOpenBracket);

    auto cond = cond_parser.parse(lxr);

    AssertExpectedToken(ParseWhileSyntaxException::kParseWhileSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokCloseBracket);

    AssertExpectedToken(ParseWhileSyntaxException::kParseWhileSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokOpenCurly);

    auto stmts = stmt_list_parser.parse(lxr);

    AssertExpectedToken(ParseWhileSyntaxException::kParseWhileSyntaxMessage,
                        lxr.GetTokAndIncrement(), Token::kTokCloseCurly);

    return std::make_unique<ast::WhileNode>(std::move(cond), std::move(stmts),
                                            stmt);
  }
};
}  // namespace sp
