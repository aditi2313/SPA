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

class AttrRefGrammar : public CompositeGrammar {
 public:
  AttrRefGrammar(
      const std::vector<std::string> &tokens,
      QueryPtr &query,
      ParseItr &itr,
      ArgumentPtr &arg)
      : CompositeGrammar(tokens, query, itr), arg_(arg) {
    // synonym
    grammar_.emplace_back(
        Grammar(
            Grammar::kSynCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              syn_name_ = *itr_;
            }));
    // '.'
    grammar_.emplace_back(
        Grammar(
            Grammar::CreateTokenCheck(PQL::kPeriodToken),
            Grammar::kEmptyAction));

    // attrName
    grammar_.emplace_back(
        Grammar(
            Grammar::kAttrNameCheck,
            [&](QueryPtr &query, const std::vector<std::string> &tokens) {
              arg_ = master_argument_factory_.CreateAttrRef(*itr_);
            }));
  }

 protected:
  SynonymName syn_name_;
  ArgumentPtr &arg_;
};
}  // namespace qps
