#pragma once
#include <unordered_map>

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

bool IsStmtToken(Token token);

}  // namespace sp
