#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "QPS/models/Query.h"
#include "QPS/models/grammar/CompositeGrammar.h"
#include "./ExactExprGrammar.h"
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

    // "expr"
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kQuotationToken),
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              ExactExprGrammar exact_expr_grammar(
                  tokens, query, itr_, arg_);
              if (!exact_expr_grammar.Parse()) {
                throw PqlSyntaxErrorException(
                    "Invalid syntax for wildcard expression");
              }

              expr_ = exact_expr_grammar.get_expr();
            }));

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
