// Temporary file to contain all the refactoring made to Lexer
// To avoid conflicts with bug fixes so they can be added
// cleanly
#include <list>
#include <memory>

#include "LexerData.h"
#include "handlers/AlphaNumericHandler.h"
#include "handlers/DoubleCharHandler.h"
#include "handlers/ErrorHandler.h"
#include "handlers/SingleCharHandler.h"
#include "handlers/WhiteSpaceHandler.h"

namespace sp {
class Lexer {
 public:
  Lexer(std::string& program)
      : data_(program), current_token_(Token::kTokError) {
    // create the handlers
    auto white_handler = std::make_unique<WhiteSpaceHandler>();
    auto alpha_handler = std::make_unique<AlphaNumericHandler>();
    auto double_handler = std::make_unique<DoubleCharHandler>();
    auto single_char_handler = std::make_unique<SingleCharHandler>();
    auto error_handler = std::make_unique<ErrorHandler>();
    handlers.push_back(std::move(white_handler));
    handlers.push_back(std::move(alpha_handler));
    handlers.push_back(std::move(double_handler));
    handlers.push_back(std::move(single_char_handler));
    handlers.push_back(std::move(error_handler));
  }

  Token get_tok() { return current_token_; }

  Token peek() {
    auto temp_data = data_;
    auto temp_curr = current_token_;

    Increment();
    auto res = get_tok();

    data_ = temp_data;
    current_token_ = temp_curr;

    return res;
  }

  void Increment();

  std::string get_word() { return data_.get_word(); }
  int get_int() { return data_.get_int(); }

 private:
  LexerData data_;
  Token current_token_;
  std::list<std::unique_ptr<LexerHandler>> handlers;
};
}  // namespace sp