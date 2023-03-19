#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/grammar/Grammar.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class CompositeGrammar {
 public:
  CompositeGrammar(
      const std::vector<std::string> &tokens,
      QueryPtr &query,
      ParseItr &itr)
      : tokens_(tokens), query_(query), itr_(itr) {}

  // Run through the actions
  inline bool Parse() {
    grammar_itr_ = grammar_.begin();
    auto saved_itr = itr_;  // Save original itr position
    bool is_syntax_match = true;

    while (itr_ != tokens_.end() && grammar_itr_ != grammar_.end()) {
      if (!(*grammar_itr_).Check(*itr_)) {
        is_syntax_match = false;
        break;
      }
      (*grammar_itr_).Action(query_, tokens_);
      grammar_itr_++;
      itr_++;
    }

    if (!is_syntax_match || grammar_itr_ != grammar_.end()) {
      itr_ = saved_itr;  // Reset itr
      return false;
    } else {
      itr_--;
      return true;
    }
  }

 protected:
  QueryPtr &query_;
  const std::vector<std::string> &tokens_;
  std::vector<Grammar> grammar_;

  ParseItr &itr_;
  GrammarItr grammar_itr_;
};
}  // namespace qps
