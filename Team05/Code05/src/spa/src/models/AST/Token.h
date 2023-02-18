#pragma once
#include <unordered_map>
#include <string>

namespace sp {

enum class Token {
    kTokEof,

    kTokProcedure,
    kTokRead,
    kTokPrint,
    kTokCall,
    kTokWhile,
    kTokIf,
    kTokElse,
    kTokThen,

    kTokIdent,
    kTokInteger,

    kTokOpenCurly,
    kTokCloseCurly,
    kTokSemicolon,
    kTokOpenBracket,
    kTokCloseBracket,

    kTokEquals,
    kTokPlus,
    kTokMinus,
    kTokTimes,
    kTokDiv,
    kTokMod,

    // relations
    kTokLess,          // <
    kTokGreater,       // >
    kTokGreaterEqual,  // >=
    kTokLessEqual,     // <=
    kTokEquiv,         // ==
    kTokNotEqual,      // !=

    // conditions
    kTokOr,
    kTokAnd,
    kTokNot,

    // error
    kTokError,
};

bool IsStmtToken(Token input);
bool IsKeyWordToken(Token token);
bool IsRelationToken(Token token);

std::string TokenToString(Token token);
}  // namespace sp
