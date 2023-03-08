#pragma once
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
  inline void add_token(std::string& token) { tokens_.push_back(token); }
  inline void add_token(std::string token) { tokens_.push_back(token); }
  inline void add_open() { tokens_.push_back("("); }
  inline void add_close() { tokens_.push_back(")"); }
  inline void add_token(sp::Token token) {
    tokens_.push_back(sp::TokenToString(token));
  }
  inline void add_const(int v) {
    tokens_.push_back(std::to_string(v));
    constants_.push_back(v);
  }
  inline void add_var(std::string& var) {
    tokens_.push_back(var);
    variables_.insert(var);
  }

  friend bool operator==(const StringExpr& LHS, const StringExpr& RHS) {
    return LHS.tokens_ == RHS.tokens_ && LHS.constants_ == RHS.constants_ &&
           LHS.variables_ == RHS.variables_;
  }

  inline static StringExpr& of() {
    expressions_.push_back(std::make_unique<StringExpr>(StringExpr()));
    return *expressions_.at(expressions_.size() - 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const StringExpr& obj) {
    for (int i = obj.tokens_.size() - 1; i >= 0; --i) {
      os << obj.tokens_.at(i);
    }
    return os;
  }

 private:
  StringExpr() {}
  // unique ptr is needed as otherwise, the reference
  // of string expr will change when the vector resizes.
  inline static std::vector<std::unique_ptr<StringExpr>> expressions_; 
  std::vector<std::string> tokens_;
  std::vector<int> constants_;
  std::unordered_set<std::string> variables_;
};

}  // namespace ast
