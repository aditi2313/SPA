#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "models/Token.h"

namespace sp {
class Lexer {
 public:
        Lexer() = default;

        // returns the type of the next token
        int GetTok();

        std::string get_ident() const { return ident_; }
        int get_integer() const { return integer_; }

 private:
    int current_char_ = ' ';
    std::string ident_;
    int integer_;
};
}  // namespace sp
