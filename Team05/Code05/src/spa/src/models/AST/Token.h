#pragma once
#include <unordered_map>

namespace sp {

enum Token {
    kTokEof,

    kTokProcedure,
    kTokRead,
    kTokPrint,
    kTokCall,
    kTokWhile,
    kTokIf,

    kTokIdent,
    kTokInteger,

    kTokOpenCurly,
    kTokCloseCurly,
    kTokSemicolon,

    kTokEquals,
    kTokPlus,
    kTokMinus,
    kTokTimes,
    kTokDiv,
    kTokMod,
};

}  // namespace sp

