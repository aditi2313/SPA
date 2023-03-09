#pragma once
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "common/Utiity.h"
#include "models/AST/Token.h"

namespace ast {
class StringExpr {
 public:
  inline void add_token(std::string& token) { tokens_.push_back(token); }
  inline void add_token(std::string token) { tokens_.push_back(token); }
  inline void add_open() { tokens_.push_back("("); }

  inline void add_close(int v) {
    tokens_[v] = ")";
    empt_count_--;
  }

  inline int insert_empty() {
    tokens_.push_back("");
    empt_count_++;
    return tokens_.size() - 1;
  }

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
    return os;
  }

  int size() const { return tokens_.size() - empt_count_; }

 private:
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
  // unique ptr is needed as otherwise, the reference
  // of string expr will change when the vector resizes.
  inline static std::vector<std::unique_ptr<StringExpr>> expressions_;
  std::vector<std::string> tokens_;
  std::vector<int> constants_;
  int empt_count_ = 0;
  std::unordered_set<std::string> variables_;
};

}  // namespace ast
