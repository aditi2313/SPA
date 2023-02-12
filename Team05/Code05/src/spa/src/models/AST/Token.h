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

}  // namespace sp
