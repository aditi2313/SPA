#pragma once

#include <memory>
#include <optional>
#include <string>

#include "models/AST/Token.h"

namespace sp {
  class LexerHandler {
  public:
    explicit LexerHandler(std::unique_ptr<LexerHandler>& next_handler) {
      next_handler_ = std::move(next_handler);
    }
    LexerHandler() { next_handler_ = nullptr; }

    virtual std::optional<Token> Handle(int& ptr, std::string& program) {
      if (!next_handler_) {
        return std::nullopt;
      }
      auto current = HandleInner(ptr, program);
      if (!current) return next_handler_->Handle(ptr, program);
      return current;
    }

  protected:
    virtual std::optional<Token> HandleInner(int&, std::string&) = 0;
    std::unique_ptr<LexerHandler> next_handler_;
  };
}  // namespace sp