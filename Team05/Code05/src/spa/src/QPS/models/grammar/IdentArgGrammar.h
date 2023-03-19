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

class IdentArgGrammar : public CompositeGrammar {
 public:
  IdentArgGrammar(
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

    // IDENT
    grammar_.emplace_back(
        Grammar(
            Grammar::kIdentCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              ident_ = *itr_;
            }));

    // "
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kQuotationToken),
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg_ = master_argument_factory_.CreateIdentArg(ident_);
            }));
  }

 protected:
  std::string ident_;
  ArgumentPtr &arg_;
};
}  // namespace qps
