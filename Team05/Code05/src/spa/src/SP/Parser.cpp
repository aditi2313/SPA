#include <iostream>
#include <utility>
#include <memory>
#include <string>

#include "models/AST/Token.h"
#include "Parser.h"
#include "Lexer.h"

namespace sp {
Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer_(std::move(lexer)) { }

int Parser::GetNextTok() {
    current_tok_ = lexer_->GetTok();
    return current_tok_;
}

void Parser::MainLoop() {
    while (true) {
        if (current_tok_ == kTokEof) {
            return;
        } else if (current_tok_ == kTokProcedure) {
            ParseProcedure();
        } else {
            GetNextTok();
        }
    }
}

void Parser::ParseProcedure() {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("procedure should be followed by a name");
    }

    std::cout << "procedure\n";

    if (GetNextTok() != kTokOpenCurly) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected '{' after procedure name");
    }

    ParseStmtLst();

    if (current_tok_ != kTokCloseCurly) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected '}' after procedure stmtLst");
    }
}

void Parser::ParseStmtLst() {
    GetNextTok();

    int stmt_count = 0;
    while (current_tok_ == kTokProcedure || current_tok_ == kTokRead
           || current_tok_ == kTokPrint || current_tok_ == kTokCall
           || current_tok_ == kTokWhile || current_tok_ == kTokIf
           || current_tok_ == kTokIdent) {
        ParseStmt();
        GetNextTok();
        stmt_count++;
    }

    if (stmt_count <= 0) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected at least 1 stmt in stmtLst");
    }
}

void Parser::ParseStmt() {
    if (current_tok_ == kTokRead) {
        ParseRead();
    } else if (current_tok_ == kTokPrint) {
        ParsePrint();
    } else if (current_tok_ == kTokCall) {
        ParseCall();
    } else if (current_tok_ == kTokWhile) {
        ParseWhile();
    } else if (current_tok_ == kTokIf) {
        ParseIf();
    } else if (current_tok_ == kTokIdent) {
        ParseExpr();
    } else {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected a stmt (read | print | call "
                                 "| while | if | assign)");
    }
}

void Parser::ParseRead() {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("read should be followed by a name");
    }

    std::cout << "read " + lexer_->get_ident() + "\n";

    if (GetNextTok() != kTokSemicolon) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected end of a statement");
    }
}

void Parser::ParsePrint() {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("print should be followed by a name");
    }

    std::cout << "print " + lexer_->get_ident() + "\n";

    if (GetNextTok() != kTokSemicolon) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected end of a statement");
    }
}

void Parser::ParseCall() {
    if (GetNextTok() != kTokIdent) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("call should be followed by a name");
    }

    std::cout << "call " + lexer_->get_ident() + "\n";

    if (GetNextTok() != kTokSemicolon) {
        // TODO(aizatazhar): use custom exception
        throw std::runtime_error("expected end of a statement");
    }
}

void Parser::ParseWhile() {
    // TODO(aizatazhar): implement
}

void Parser::ParseIf() {
    // TODO(aizatazhar): implement
}

void Parser::ParseExpr() {
    if (current_tok_ == kTokIdent) {
        std::cout << lexer_->get_ident();
    } else if (current_tok_ == kTokInteger) {
        std::cout << lexer_->get_integer();
    }

    GetNextTok();

    while (current_tok_ != kTokSemicolon) {
        if (current_tok_ != kTokEquals && current_tok_ != kTokPlus
            && current_tok_ != kTokMinus && current_tok_ != kTokTimes
            && current_tok_ != kTokDiv && current_tok_ != kTokMod
            && current_tok_ != kTokIdent && current_tok_ != kTokInteger) {
            // TODO(aizatazhar): use custom exception
            throw std::runtime_error("expected an expression");
        }

        std::cout << " " + std::to_string(current_tok_) + " ";

        GetNextTok();  // eat the operator

        ParseExpr();
    }
}
}  // namespace sp
