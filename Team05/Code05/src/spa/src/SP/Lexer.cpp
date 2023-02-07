#include "Lexer.h"

#include <stdexcept>
#include <utility>

namespace sp {

Lexer::Lexer(std::string program) : program_(std::move(program)) {
  this->pointer_ = 0;
  this->current_char_ = ' ';
}

bool Lexer::IsCurrentTokenAdd() { return current_char_ == '+'; }
bool Lexer::IsCurrentTokenCloseCurly() { return current_char_ == '}'; }
bool Lexer::IsCurrentTokenOpenCurly() { return current_char_ == '}'; }
bool Lexer::IsCurrentTokenDiv() { return current_char_ == '/'; }
// bool Lexer::IsCurrentTokenEof() { return false }

int Lexer::GetTok() {
  if (pointer_ >= program_.length()) {
    return kTokEof;
  }

  // ignore whitespaces
  while (isspace(current_char_)) {
    current_char_ = program_[pointer_++];
  }

  //  current token is an IDENT
  if (isalpha(current_char_)) {
    ident_ = current_char_;

    while (isalnum(current_char_ = program_[pointer_++])) {
      ident_ += current_char_;
    }

    if (ident_ == "procedure") {
      return kTokProcedure;
    } else if (ident_ == "read") {
      return kTokRead;
    } else if (ident_ == "print") {
      return kTokPrint;
    } else if (ident_ == "call") {
      return kTokCall;
    } else if (ident_ == "while") {
      return kTokWhile;
    } else if (ident_ == "if") {
      return kTokIf;
    } else {
      return kTokIdent;
    }
  }

  // current token is an INTEGER
  if (isdigit(current_char_)) {
    std::string number_string;
    number_string += current_char_;

    while (isdigit(current_char_ = program_[pointer_++])) {
      number_string += current_char_;
      current_char_ = program_[pointer_++];
    }

    ValidateInteger(number_string);

    integer_ = std::stoi(number_string);
    return kTokInteger;
  }

  if (current_char_ == '{') {
    current_char_ = program_[pointer_++];
    return kTokOpenCurly;
  }

  if (current_char_ == '}') {
    current_char_ = program_[pointer_++];
    return kTokCloseCurly;
  }

  if (current_char_ == ';') {
    current_char_ = program_[pointer_++];
    return kTokSemicolon;
  }

  if (current_char_ == '=') {
    current_char_ = program_[pointer_++];
    return kTokEquals;
  }

  if (current_char_ == '+') {
    current_char_ = program_[pointer_++];
    return kTokPlus;
  }

  if (current_char_ == '-') {
    current_char_ = program_[pointer_++];
    return kTokMinus;
  }

  if (current_char_ == '*') {
    current_char_ = program_[pointer_++];
    return kTokTimes;
  }

  if (current_char_ == '/') {
    current_char_ = program_[pointer_++];
    return kTokDiv;
  }

  if (current_char_ == '%') {
    current_char_ = program_[pointer_++];
    return kTokMod;
  }

  return current_char_;
}

void Lexer::ValidateInteger(std::string number_string) {
  if (number_string[0] == '0' && number_string.length() > 1) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("integer cannot have leading zeroes");
  }
}
}  // namespace sp
