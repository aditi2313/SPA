#include "Lexer.h"

#include <optional>
#include <stdexcept>
#include <utility>

namespace sp {

Lexer::Lexer(std::string program) : program_(std::move(program)) {
  this->pointer_ = 0;
  Increment();
}

// TODO(Gab) Replace this logic using the token class #40
std::optional<Token> ProcessSpecialChars(char c) {
  switch (c) {
    case '{':
      return {Token::kTokOpenCurly};
    case '}':
      return {Token::kTokCloseCurly};
    case ';':
      return {Token::kTokSemicolon};
    case '=':
      return {Token::kTokEquals};
    case '+':
      return {Token::kTokPlus};
    case '-':
      return {Token::kTokMinus};
    case '*':
      return {Token::kTokTimes};
    case '/':
      return {Token::kTokDiv};
    case '%':
      return {Token::kTokMod};
    case '(':
      return {Token::kTokOpenBracket};
    case ')':
      return {Token::kTokCloseBracket};

    default:
      return std::nullopt;
  }
}

int Lexer::get_tok() { return current_tok_; }

bool Lexer::ReadWord() {
  int p = pointer_;
  char c = program_[p];
  if (!(isalnum(c))) {
    return false;
  }
  word_ = c;
  while (isalnum(c = program_[++p])) {
    word_ += c;
  }
  pointer_ = p;
  return true;
}

bool Lexer::ReadInt() {
  std::string result_int;
  int p = pointer_;
  char current_char = program_[p++];
  if (!isdigit(current_char)) {
    return false;
  }
  // current token is an INTEGER
  std::string number_string;
  number_string += current_char;
  while (isdigit(current_char = program_[p++])) {
    number_string += current_char;
    current_char = program_[p++];
  }
  ValidateInteger(number_string);
  integer_ = std::stoi(number_string);
  current_tok_ = Token::kTokInteger;
  pointer_ = p;
  return true;
}

void Lexer::Increment() {
  if (pointer_ >= program_.length()) {
    current_tok_ = Token::kTokEof;
    return;
  }
  // ignore whitespaces
  char c = program_[pointer_];
  while (isspace(c)) {
    c = program_[++pointer_];
  }
  if (ReadWord()) {
    if (word_ == "procedure") {
      current_tok_ = Token::kTokProcedure;
    } else if (word_ == "read") {
      current_tok_ = Token::kTokRead;
    } else if (word_ == "print") {
      current_tok_ = Token::kTokPrint;
    } else if (word_ == "call") {
      current_tok_ = Token::kTokCall;
    } else if (word_ == "while") {
      current_tok_ = Token::kTokWhile;
    } else if (word_ == "if") {
      current_tok_ = Token::kTokIf;
    } else {
      current_tok_ = Token::kTokIdent;
    }
    return;
  }

  int p = pointer_;
  auto new_token = ReadRelation(p);
  if (new_token.has_value()) {
    current_tok_ = new_token.value();
    pointer_ = p;
    return;
  }

  new_token = ProcessSpecialChars(c);
  if (new_token.has_value()) {
    current_tok_ = new_token.value();
    pointer_++;
    return;
  }

  ReadInt();
}

void Lexer::ValidateInteger(std::string number_string) {
  if (number_string[0] == '0' && number_string.length() > 1) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("integer cannot have leading zeroes");
  }
}

// Todo(Gab) refactor in sp/rel-parser
// out of this class
Token ParseLessGreater(char c) {
  if (c == '<') return Token::kTokLess;
  if (c == '>') return Token::kTokGreater;
  throw std::runtime_error("Invalid input into ParseLessGreater");
}

std::optional<Token> ParseLessGreaterEqual(char c) {
  if (c == '<') return {Token::kTokLessEqual};
  if (c == '>') return {Token::kTokGreaterEqual};
  return std::nullopt;
}

// Temporary utility function. Todo(Gab): reorganise in sp/rel-parser
std::optional<Token> Lexer::ReadRelation(int& pointer) {
  // check for < or >
  char c = program_[pointer];
  if (c == '=' && pointer + 1 < program_.length() &&
      program_[pointer + 1] == '=') {
    pointer += 2;
    return {Token::kTokEquiv};
  }

  if (c == '>' || c == '<') {
    pointer++;
    if (pointer >= program_.length()) {
      pointer++;
      return {ParseLessGreater(c)};
    }
    if (program_[pointer] == '=') {
      pointer++;
      return {ParseLessGreaterEqual(c)};
    }
    return {ParseLessGreater(c)};
  }

  if (c == '&' || c == '|') {
    pointer++;
    if (pointer >= program_.length()) {
      return Token::kTokEof;
    }
    if (program_[pointer] != c) {
      return {Token::kTokError};
    }
    pointer++;
    if (c == '&') {
      return {Token::kTokAnd};
    }
    if (c == '|') {
      return {Token::kTokOr};
    }
  }
  return std::nullopt;
}
}  // namespace sp
