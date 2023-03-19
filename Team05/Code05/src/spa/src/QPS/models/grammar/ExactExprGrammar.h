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

class ExactExprGrammar : public CompositeGrammar {
 public:
  ExactExprGrammar(
      const std::vector<std::string> &tokens,
      QueryPtr &query,
      ParseItr &itr,
      ArgumentPtr &arg)
      : CompositeGrammar(tokens, query, itr), arg_(arg) {
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
              if (*itr_ == PQL::kQuotationToken) {
                itr--;  // Don't consume token
              } else {
                expr_ += *itr_;
                grammar_itr_--;  // Stay in this grammar
              }
            }));
    // "
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kQuotationToken),
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg_ = master_argument_factory_.CreateExpressionArg(expr_, true);
            }));
  }

  inline std::string get_expr() {
    return expr_;
  }

 protected:
  std::string expr_;
  ArgumentPtr &arg_;
};
}  // namespace qps
