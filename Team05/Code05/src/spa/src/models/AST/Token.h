#pragma once
#include <unordered_map>

namespace sp {

enum Token {
    kTokEof,

    kTokProcedure,

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

