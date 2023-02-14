#pragma once

#include <string>

/// <summary>
/// Class representing the data stored in the lexer.
/// </summary>
class LexerData {
 public:
  explicit LexerData(std::string& program) : program_(program) {
    ptr_ = 0;
    current_stmt_ = 1;
    current_int_ = -1;
    word_ = "";
  }

  LexerData(const LexerData& data) : program_(data.program_) {
    ptr_ = data.ptr_;
    current_stmt_ = data.current_stmt_;
    current_int_ = data.current_int_;
    word_ = data.word_;
  }

  LexerData& operator=(const LexerData& data) {
    this->current_int_ = data.current_int_;
    this->current_stmt_ = data.current_stmt_;
    this->program_ = data.program_;
    this->ptr_ = data.ptr_;
    this->word_ = data.word_;
    return *this;
  }

  inline int GetStmtAndIncrment() { return current_stmt_++; }

  inline int get_int() { return current_int_; }

  inline std::string get_ident() { return word_; }
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

  inline void set_word(std::string& word) { word_ = word; }
  inline void set_int(int val) { current_int_ = val; }

 private:
  std::string word_;
  int current_int_;
  int current_stmt_;
  std::string& program_;
  int ptr_;
};
