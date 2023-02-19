#pragma once

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "LexerData.h"
#include "handlers/AlphaNumericHandler.h"
#include "handlers/DoubleCharHandler.h"
#include "handlers/IntegerHandler.h"
#include "handlers/SingleCharHandler.h"
#include "handlers/WhiteSpaceHandler.h"

namespace sp {
class Lexer {
 public:
  explicit Lexer(std::string program) : data_(program) {
    // create the handlers
    auto white_handler = std::make_unique<WhiteSpaceHandler>();
    auto alpha_handler = std::make_unique<AlphaNumericHandler>();
    auto double_handler = std::make_unique<DoubleCharHandler>();
    auto single_char_handler = std::make_unique<SingleCharHandler>();
    auto int_handler = std::make_unique<IntegerHandler>();
    handlers.push_back(std::move(white_handler));
    handlers.push_back(std::move(alpha_handler));
    handlers.push_back(std::move(double_handler));
    handlers.push_back(std::move(single_char_handler));
    handlers.push_back(std::move(int_handler));
    Increment();
  }

  Token GetTokAndIncrement() {
    auto tok = get_tok();
    Increment();
    return tok;
  }

  int GetAndIncrementStmtCtr() { return data_.GetStmtAndIncrement(); }

  Token get_tok() { return data_.get_current_token(); }

  Token Peek() {
    auto temp_data = data_;

    Increment();
    auto res = get_tok();

    data_ = temp_data;

    return res;
  }

  void Increment();

  std::string get_ident() { return data_.get_ident(); }
  int get_integer() { return data_.get_int(); }

 private:
  LexerData data_;
  std::list<std::unique_ptr<LexerHandler>> handlers;
};
}  // namespace sp
