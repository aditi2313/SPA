#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/grammar/CompositeGrammar.h"
#include "QPS/factories/MasterArgumentFactory.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
extern MasterArgumentFactory master_argument_factory_;

class WildcardExprGrammar : public CompositeGrammar {
 public:
  WildcardExprGrammar(
      std::vector<std::string> &tokens,
      QueryPtr &query,
      ParseItr &itr,
      ArgumentPtr &arg)
      : CompositeGrammar(tokens, query, itr), arg_(arg) {
    // _
    grammar_.emplace_back(
        Grammar(
            Grammar::kWildcardCheck,
            Grammar::kEmptyAction));
    // "expr"
    grammar_.emplace_back(
        Grammar(
            Grammar::kExactExprCheck,
            [&](QueryPtr &query) {
              expr_ = *itr_;
            }));
    // _
    grammar_.emplace_back(
        Grammar(
            Grammar::kWildcardCheck,
            [&](QueryPtr &query) {
              arg_ = master_argument_factory_.CreateExpressionArg(expr_, false);
            }));
  }

 protected:
  std::string expr_;
  ArgumentPtr &arg_;
};
}  // namespace qps
