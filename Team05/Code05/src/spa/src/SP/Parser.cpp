#include <iostream>
#include <utility>
#include <memory>
#include <string>

#include "Parser.h"
#include "Lexer.h"
#include "models/AST/Token.h"

namespace sp {
Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer_(std::move(lexer)) {
    root_ = std::make_unique<ast::ProgramNode>(
            ast::ProgramNode(std::vector<std::unique_ptr<ast::ProcNode>>()));
}

int Parser::GetNextTok() {
    current_tok_ = lexer_->GetTok();
    return current_tok_;
}

std::unique_ptr<ast::ProgramNode> Parser::ParseProgram() {
    while (true) {
        if (current_tok_ == kTokEof) {
            break;
        } else if (current_tok_ == kTokProcedure) {
            root_->add_proc(std::move(ParseProcedure()));
        } else {
            GetNextTok();
        }
    }

    return std::move(root_);
}

std::unique_ptr<ast::ProcNode> Parser::ParseProcedure() {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("procedure should be followed by a name");
    }

    std::string proc_name = lexer_->get_ident();
    std::cout << "procedure\n";

    if (GetNextTok() != kTokOpenCurly) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected '{' after procedure name");
    }

    std::unique_ptr<ast::ProcNode> proc_node = std::make_unique<ast::ProcNode>(
            ast::ProcNode(proc_name, std::move(ParseStmtLst())));

    if (current_tok_ != kTokCloseCurly) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected '}' after procedure stmtLst");
    }

    return proc_node;
}

std::unique_ptr<ast::StmtLstNode> Parser::ParseStmtLst() {
    GetNextTok();

    std::vector<std::unique_ptr<ast::StmtNode>> stmt_nodes;
    while (current_tok_ == kTokProcedure || current_tok_ == kTokRead
           || current_tok_ == kTokPrint || current_tok_ == kTokCall
           || current_tok_ == kTokWhile || current_tok_ == kTokIf
           || current_tok_ == kTokIdent) {
        stmt_nodes.push_back(std::move(ParseStmt(stmt_nodes.size() + 1)));
        GetNextTok();
    }

    if (stmt_nodes.empty()) {
        throw std::runtime_error("expected at least 1 stmt in stmtLst");
    }

    auto stmt_lst_node = std::make_unique<ast::StmtLstNode>(
            ast::StmtLstNode(std::move(stmt_nodes)));
    return stmt_lst_node;
}

std::unique_ptr<ast::StmtNode> Parser::ParseStmt(int line) {
    if (current_tok_ == kTokRead) {
        return ParseRead(line);
    } else if (current_tok_ == kTokPrint) {
        return ParsePrint(line);
    } else if (current_tok_ == kTokCall) {
        return ParseCall(line);
    } else if (current_tok_ == kTokWhile) {
        ParseWhile();
        return nullptr;
    } else if (current_tok_ == kTokIf) {
        ParseIf();
        return nullptr;
    } else if (current_tok_ == kTokIdent) {
        return ParseAssign(line);
    } else {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected a stmt (read | print | call "
                                 "| while | if | assign)");
    }
}

std::unique_ptr<ast::ReadNode> Parser::ParseRead(int line) {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("read should be followed by a name");
    }

    std::string var_name = lexer_->get_ident();
    std::cout << "read " + lexer_->get_ident() + "\n";

    if (GetNextTok() != kTokSemicolon) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected end of a statement");
    }

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::ReadNode>(
            ast::ReadNode(std::move(var_node), line));
}

std::unique_ptr<ast::PrintNode> Parser::ParsePrint(int line) {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("print should be followed by a name");
    }

    std::string var_name = lexer_->get_ident();
    std::cout << "print " + lexer_->get_ident() + "\n";

    if (GetNextTok() != kTokSemicolon) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected end of a statement");
    }

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::PrintNode>(
            ast::PrintNode(std::move(var_node), line));
}

std::unique_ptr<ast::CallNode> Parser::ParseCall(int line) {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("call should be followed by a name");
    }

    std::string var_name = lexer_->get_ident();
    std::cout << "call " + lexer_->get_ident() + "\n";

    if (GetNextTok() != kTokSemicolon) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected end of a statement");
    }

    auto var_node = std::make_unique<ast::VarNode>(ast::VarNode(var_name));
    return std::make_unique<ast::CallNode>(
            ast::CallNode(std::move(var_node), line));
}

void Parser::ParseWhile() {
    // TODO(aizatazhar): implement
}

void Parser::ParseIf() {
    // TODO(aizatazhar): implement
}

std::unique_ptr<ast::AssignNode> Parser::ParseAssign(int line) {
    auto var_node = std::make_unique<ast::VarNode>(
            ast::VarNode(lexer_->get_ident()));

    if (GetNextTok() != kTokEquals) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected '=' in assignment");
    }

    return std::make_unique<ast::AssignNode>(
            ast::AssignNode(std::move(var_node), ParseExpr(), line));
}

std::unique_ptr<ast::ExprNode> Parser::ParseExpr() {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected an expression");
    }

    auto lhs = std::make_unique<ast::VarNode>(
            ast::VarNode(lexer_->get_ident()));

    int op = GetNextTok();

    GetNextTok();

    auto rhs = std::make_unique<ast::VarNode>(
            ast::VarNode(lexer_->get_ident()));

    if (op == kTokPlus) {
        GetNextTok();
        return std::make_unique<ast::PlusNode>(
                ast::PlusNode(std::move(rhs), std::move(lhs)));
    } else if (op == kTokMinus) {
        GetNextTok();
        return std::make_unique<ast::MinusNode>(
                ast::MinusNode(std::move(rhs), std::move(lhs)));
    } else {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("unknown token");
    }
}

void Parser::ParseTerm() {
    // TODO(aizatazhar): implement
}

std::unique_ptr<ast::FactorNode> Parser::ParseFactor() {
    GetNextTok();

    if (current_tok_ == kTokIdent) {
        return std::make_unique<ast::FactorNode>(
                ast::VarNode(lexer_->get_ident()));
    } else if (current_tok_ == kTokInteger) {
        return std::make_unique<ast::FactorNode>(
                ast::ConstNode(lexer_->get_integer()));
    } else {
        // TODO(aizatazhar): parentheses support
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected an expression");
    }
}
}  // namespace sp
