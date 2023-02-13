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

bool Lexer::ReadWord(int &temp_pointer) {
  char c = program_[temp_pointer];
  // NAME: LETTER (LETTER | DIGIT)*
  if (!isalpha(c)) {
    return false;
  }

  word_ = c;
  while (isalnum(c = program_[++temp_pointer])) {
    word_ += c;
  }

  return true;
}

bool Lexer::ReadInt(int &temp_pointer) {
  std::string result_int;
  char current_char = program_[temp_pointer];
  if (!isdigit(current_char)) {
    return false;
  }

  // current token is an INTEGER
  // INTEGER : 0 | NZDIGIT ( DIGIT )*
  std::string number_string;
  while (temp_pointer < program_.length() && !isspace(current_char)
         && current_char != ';') {
    number_string += current_char;
    current_char = program_[++temp_pointer];
  }

  ValidateInteger(number_string);
  integer_ = std::stoi(number_string);

  return true;
}

void Lexer::Increment() {
  auto next_token_and_pointer = PeekTokenAndPointer();
  current_tok_ = next_token_and_pointer.first;
  pointer_ = next_token_and_pointer.second;
}

int Lexer::Peek() {
  return Lexer::PeekTokenAndPointer().first;
}

std::pair<int, int> Lexer::PeekTokenAndPointer() {
  // don't update pointer_ when peeking
  int p = pointer_;

  if (p >= program_.length()) {
    return {Token::kTokEof, p};
  }

  // ignore whitespaces
  char c = program_[p];
  while (isspace(c)) {
    c = program_[++p];
  }

  if (ReadWord(p)) {
    if (word_ == "procedure") {
      return {Token::kTokProcedure, p};
    } else if (word_ == "read") {
      return {Token::kTokRead, p};
    } else if (word_ == "print") {
      return {Token::kTokPrint, p};
    } else if (word_ == "call") {
      return {Token::kTokCall, p};
    } else if (word_ == "while") {
      return {Token::kTokWhile, p};
    } else if (word_ == "if") {
      return {Token::kTokIf, p};
    } else {
      return {Token::kTokIdent, p};
    }
  }

  auto new_token = ProcessLengthTwoTokens(p);
  if (new_token.has_value()) {
    return {new_token.value(), p};
  }

  new_token = ProcessSpecialChars(c);
  if (new_token.has_value()) {
    return {new_token.value(), p};
  }

  if (ReadInt(p)) {
    return {kTokInteger, p};
  }

  throw std::runtime_error("Lexer unknown token");
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
