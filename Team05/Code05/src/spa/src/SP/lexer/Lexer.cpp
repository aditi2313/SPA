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
    case '!':
      return {Token::kTokNot};
    case '<':
      return {Token::kTokLess};
    case '>':
      return {Token::kTokGreater};
    default:
      return std::nullopt;
  }
}

bool Lexer::ReadWord() {
  int p = pointer_;
  char c = program_[p];
  // NAME: LETTER (LETTER | DIGIT)*
  if (!isalpha(c)) {
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
  char current_char = program_[p];
  if (!isdigit(current_char)) {
    return false;
  }

  // current token is an INTEGER
  // INTEGER : 0 | NZDIGIT ( DIGIT )*
  std::string number_string;
  while (p < program_.length() && !isspace(current_char)
         && current_char != ';') {
    number_string += current_char;
    current_char = program_[++p];
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
  auto new_token = ProcessLengthTwoTokens(p);
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

int Lexer::Peek() {
  int original_pointer = pointer_;
  int original_tok = current_tok_;
  std::string original_ident = get_ident();
  int original_integer = get_integer();

  Increment();
  int res = get_tok();

  current_tok_ = original_tok;
  pointer_ = original_pointer;
  word_ = original_ident;
  integer_ = original_integer;

  return res;
}

void Lexer::ValidateInteger(std::string number_string) {
  if (number_string[0] == '0' && number_string.length() > 1) {
    // TODO(aizatazhar): use custom exception
    throw std::runtime_error("integer cannot have leading zeroes");
  }

  for (int i = 0; i < number_string.length(); i++) {
    if (!isdigit(number_string[i])) {
      // TODO(aizatazhar): use custom exception
      throw std::runtime_error("integer cannot have non-digits");
    }
  }
}

std::optional<Token> Lexer::ProcessLengthTwoTokens(int& pointer) {
  if (pointer + 1 >= program_.length()) return std::nullopt;
  std::string relation =
      std::string() + program_[pointer] + program_[pointer + 1];
  pointer += 2;
  if (relation == "!=") {
    return {Token::kTokNotEqual};
  }
  if (relation == "==") {
    return {Token::kTokEquiv};
  }
  if (relation == "<=") {
    return {Token::kTokLessEqual};
  }
  if (relation == ">=") {
    return {Token::kTokGreaterEqual};
  }
  if (relation == "||") {
    return {Token::kTokOr};
  }
  if (relation == "&&") {
    return {Token::kTokAnd};
  }
  return std::nullopt;
}
}  // namespace sp
