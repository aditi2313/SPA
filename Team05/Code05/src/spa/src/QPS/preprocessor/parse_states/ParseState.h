#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/grammar/Grammar.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ParseState {
 public:
  explicit ParseState(std::string transition)
      : kTransitionKeyword(transition) {}

  void Parse(const std::vector<std::string> &tokens,
             ParseItr &itr, QueryPtr &query);

  inline virtual bool is_transition_keyword(std::string token) {
    return token == kTransitionKeyword;
  }

  inline bool has_semantic_error() {
    return has_semantic_error_;
  }

  virtual ~ParseState() = default;

 protected:
  inline void ThrowException() {
    throw PqlSyntaxErrorException(kExceptionMessage);
  }

  inline virtual bool IsComplete(GrammarItr grammar_itr) {
    for (auto &pos : end_states_) {
      if (grammar_itr == pos) return true;
    }
    return false;
  }

  const char *kExceptionMessage;
  std::string kTransitionKeyword;

  std::vector<Grammar> grammar_;
  std::vector<GrammarItr> end_states_;

  ParseItr itr_;
  GrammarItr grammar_itr_;

  bool has_semantic_error_ = false;
};
}  // namespace qps
