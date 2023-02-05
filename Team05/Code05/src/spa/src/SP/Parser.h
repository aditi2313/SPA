#pragma once

#include <unordered_set>
#include <memory>
#include <vector>

#include "Lexer.h"
#include "models/AST/TNode.h"
#include "models/AST/ProgramNode.h"
#include "models/AST/ProcNode.h"
#include "models/AST/StmtLstNode.h"
#include "models/AST/stmt_node/StmtNode.h"

namespace sp {
class Parser {
 public:
    explicit Parser(std::unique_ptr<Lexer> lexer);

    std::unique_ptr<ast::ProgramNode> ParseProgram();

    // temporary for simplified pattern matching
    static std::unique_ptr<ast::ExprNode> ParseExpr(std::string expr);
 private:
    std::unique_ptr<Lexer> lexer_;
    int current_tok_;
    std::unique_ptr<ast::ProgramNode> root_;

    int GetNextTok();

    std::unique_ptr<ast::ProcNode> ParseProcedure();

    std::unique_ptr<ast::StmtLstNode> ParseStmtLst();
    std::unique_ptr<ast::StmtNode> ParseStmt(int line);

    std::unique_ptr<ast::ReadNode> ParseRead(int line);
    std::unique_ptr<ast::PrintNode> ParsePrint(int line);
    std::unique_ptr<ast::CallNode> ParseCall(int line);
    void ParseWhile();
    void ParseIf();
    std::unique_ptr<ast::AssignNode> ParseAssign(int line);

    std::unique_ptr<ast::ExprNode> ParseExpr();
    void ParseTerm();
    std::unique_ptr<ast::FactorNode> ParseFactor();
};
}  // namespace sp
