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
      const std::vector<std::string> &tokens,
      QueryPtr &query,
      ParseItr &itr,
      ArgumentPtr &arg)
      : CompositeGrammar(tokens, query, itr), arg_(arg) {
    // _
    grammar_.emplace_back(
        Grammar(
            Grammar::kWildcardCheck,
            Grammar::kEmptyAction));
    // "
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kQuotationToken),
            Grammar::kEmptyAction));
    // expr
    grammar_.emplace_back(
        Grammar(
            Grammar::kTrueCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              expr_ = *itr_;
            }));
    // "
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kQuotationToken),
            Grammar::kEmptyAction));

    // _
    grammar_.emplace_back(
        Grammar(
            Grammar::kWildcardCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg_ = master_argument_factory_.CreateExpressionArg(expr_, false);
            }));
  }

 protected:
  std::string expr_;
  ArgumentPtr &arg_;
};
}  // namespace qps
