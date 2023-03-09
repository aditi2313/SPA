#pragma once
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/Utiity.h"
#include "models/AST/Token.h"

namespace ast {
class StringExpr {
 public:
  inline void add_token(std::string& token) { push_back(token); }
  inline void add_token(std::string token) { push_back(token); }
  inline void add_open() {
    std::string close = "(";
    push_back(close);
  }

  inline void add_close(int v) {
    tokens_[v] = ")";

    size_++;
  }

  inline int insert_empty() {
    std::string empt = "";
    push_back(empt);

    return tokens_.size() - 1;
  }

  inline void add_token(sp::Token token) {
    std::string tok = sp::TokenToString(token);
    push_back(tok);
  }
  inline void add_const(int v) {
    auto v_str = std::to_string(v);
    push_back(v_str);
    constants_.insert(mac buiv);
  }

  inline void add_var(std::string& var) {
    push_back(var);
    variables_.insert(var);
  }

  friend bool operator==(const StringExpr& LHS, const StringExpr& RHS) {
    return LHS.CompareVectors(RHS, 0) && LHS.constants_ == RHS.constants_ &&
           LHS.variables_ == RHS.variables_ && LHS.size() == RHS.size();
  }

  inline static StringExpr& of() {
    expressions_.push_back(std::make_unique<StringExpr>(StringExpr()));
    return *expressions_.at(expressions_.size() - 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const StringExpr& obj) {
    for (auto iter = obj.tokens_.end(); iter != obj.tokens_.begin();) {
      --iter;
      os << *iter;
    }
    os << " size:" << obj.size_;
    return os;
  }

  int size() const { return size_; }

  bool Contains(const StringExpr& other) const;

 private:
  void push_back(std::string& str) {
    size_ += str.length();
    tokens_.push_back(str);
  }
  bool CompareVectors(const StringExpr& other, int i) const {
    auto other_ptr = other.tokens_.begin();
    for (int k = i; k < tokens_.size() && other_ptr != other.tokens_.end();
         k++) {
      if (tokens_[k] == "") {
        continue;
      }
      while (*other_ptr == "") {
        other_ptr++;
      }
      if (*other_ptr != tokens_[k]) {
        return false;
      }
      other_ptr++;
    }
    return true;
  }

  StringExpr() {}
  size_t size_ = 0;
  // unique ptr is needed as otherwise, the reference
  // of string expr will change when the vector resizes.
  inline static std::vector<std::unique_ptr<StringExpr>> expressions_;
  std::vector<std::string> tokens_;
  std::unordered_set<int> constants_;
  inline static const char kEmpty[] = "";

  std::unordered_set<std::string> variables_;
};

}  // namespace ast
