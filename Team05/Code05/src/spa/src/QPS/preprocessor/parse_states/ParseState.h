#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/Grammar.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ParseState {
 public:
  using ParseItr = std::vector<std::string>::iterator;
  using GrammarItr = std::vector<Grammar>::iterator;

  std::string kTransitionKeyword;

  explicit ParseState(std::string transition)
      : kTransitionKeyword(transition) {}

  void Parse(const std::vector<std::string> &tokens,
             ParseItr &itr, QueryPtr &query);

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

  std::vector<Grammar> grammar_;
  std::vector<GrammarItr> end_states_;

  ParseItr itr_;
  GrammarItr grammar_itr_;
};
}  // namespace qps
