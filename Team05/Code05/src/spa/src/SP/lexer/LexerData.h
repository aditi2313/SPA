#pragma once

#include <string>
#include <utility>
#include "models/AST/Token.h"

/// <summary>
/// Class representing the data stored in the lexer.
/// </summary>
class LexerData {
 public:
  explicit LexerData(std::string& program) : program_(program) {
    ptr_ = 0;
    current_stmt_ = 1;
    current_int_ = -1;
    current_procedure_ = "";
    current_token_ = sp::Token::kTokError;
    word_ = "";
  }

  LexerData(const LexerData& data) : program_(data.program_) {
    ptr_ = data.ptr_;
    current_stmt_ = data.current_stmt_;
    current_int_ = data.current_int_;
    current_procedure_ = data.current_procedure_;
    current_token_ = data.current_token_;
    word_ = data.word_;
  }

  LexerData& operator=(const LexerData& data) {
    this->current_int_ = data.current_int_;
    this->current_stmt_ = data.current_stmt_;
    this->current_token_ = data.current_token_;
    this->current_procedure_ = data.current_procedure_;
    this->program_ = data.program_;
    this->ptr_ = data.ptr_;
    this->word_ = data.word_;
    return *this;
  }

  inline int GetStmtAndIncrement() { return current_stmt_++; }

  inline int get_int() { return current_int_; }

  inline sp::Token get_current_token() { return current_token_; }
  inline std::string get_ident() { return word_; }
  inline std::string get_current_procedure() { return current_procedure_; }
  inline char get_current_char() { return program_[ptr_]; }

  /// <summary>
  /// Increments the pointer to the program.
  /// </summary>
  inline void increment_pointer() { ptr_++; }

  /// <summary>
  /// Decrements the pointer to the program.
  /// </summary>
  inline void decrement_pointer() { ptr_--; }
  inline bool is_end() { return ptr_ >= program_.length(); }

  inline void set_current_token(sp::Token token) { current_token_ = token; }
  inline void set_current_procedure(std::string proc) {
    current_procedure_ = std::move(proc);
  }
  inline void set_word(std::string& word) { word_ = word; }
  inline void set_int(int val) { current_int_ = val; }

 private:
  std::string word_;
  sp::Token current_token_;
  int current_int_;
  int current_stmt_;
  std::string current_procedure_;
  std::string& program_;
  int ptr_;
};
