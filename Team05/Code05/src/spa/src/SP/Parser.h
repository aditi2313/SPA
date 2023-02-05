#pragma once

#include "Lexer.h"
#include <unordered_set>
#include <memory>

namespace sp {
class Parser {
 public:
    explicit Parser(std::unique_ptr<Lexer> lexer);

    void MainLoop();

 private:
        std::unique_ptr<Lexer> lexer_;

        int GetNextTok();

        void ParseProcedure();

        void ParseStmtLst();
        void ParseStmt();

        void ParseRead();
        void ParsePrint();
        void ParseCall();
        void ParseWhile();
        void ParseIf();
        void ParseExpr();
};
}  // namespace sp
