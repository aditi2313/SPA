#include <iostream>
#include "Lexer.h"

namespace sp {

int Lexer::GetTok() {
    // ignore whitespaces
    while (isspace(current_char_)) {
        current_char_ = getchar();
    }

    //  current token is an IDENT
    if (isalpha(current_char_)) {
        ident_ = current_char_;

        while (isalnum(current_char_ = getchar())) {
            ident_ += current_char_;
        }

        if (ident_ == "procedure") {
            return kTokProcedure;
        } else {
            return kTokIdent;
        }
    }

    // current token is an INTEGER
    if (isdigit(current_char_)) {
        std::string number_string;
        number_string += current_char_;

        while (isdigit(current_char_ = getchar())) {
            number_string += current_char_;
            current_char_ = getchar();
        }

        if (number_string[0] == '0' && number_string.length() > 1) {
            throw std::runtime_error("integer cannot have leading zeroes");
        }

        integer_ = std::stoi(number_string);
        return kTokInteger;
    }

    if (current_char_ == '{') {
        current_char_ = getchar();
        return kTokOpenCurly;
    }

    if (current_char_ == '}') {
        current_char_ = getchar();
        return kTokCloseCurly;
    }

    if (current_char_ == ';') {
        current_char_ = getchar();
        return kTokSemicolon;
    }

    if (current_char_ == '=') {
        current_char_ = getchar();
        return kTokEquals;
    }

    if (current_char_ == '+') {
        current_char_ = getchar();
        return kTokPlus;
    }

    if (current_char_ == '-') {
        current_char_ = getchar();
        return kTokMinus;
    }

    if (current_char_ == '*') {
        current_char_ = getchar();
        return kTokTimes;
    }

    if (current_char_ == '/') {
        current_char_ = getchar();
        return kTokDiv;
    }

    if (current_char_ == '%') {
        current_char_ = getchar();
        return kTokMod;
    }

    if (current_char_ == EOF) {
        current_char_ = getchar();
        return kTokEof;
    }

    return current_char_;
}
}  // namespace sp

