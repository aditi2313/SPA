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
      std::vector<std::string> &tokens,
      QueryPtr &query,
      ParseItr &itr)
      : tokens_(tokens), query_(query), itr_(itr) {}

  // Run through the actions
  inline bool Parse() {
    grammar_itr_ = grammar_.begin();
    auto itr = itr_;  // Copy itr

    while (itr != tokens_.end() && grammar_itr_ != grammar_.end()) {
      if (!(*grammar_itr_).Check(*itr)) return false;
      (*grammar_itr_).Action(query_);
      grammar_itr_++;
      itr++;
    }

    if(grammar_itr_ != grammar_.end()) return false;
    return true;
  }


 protected:
  QueryPtr &query_;
  std::vector<std::string> &tokens_;
  std::vector<Grammar> grammar_;

  ParseItr &itr_;
  GrammarItr grammar_itr_;
};
}  // namespace qps
