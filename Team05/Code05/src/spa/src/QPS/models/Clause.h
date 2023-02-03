#pragma once

#include <memory>

#include "Argument.h"
#include "PKB/PKBRead.h"
#include "QPS/models/QueryResult.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  virtual QueryResult Evaluate(const std::unique_ptr<pkb::PKBRead> &pkb) = 0;

 private:
  Argument arg1;
  Argument arg2;
};

class ModifiesClause : Clause {
  QueryResult Evaluate(const std::unique_ptr<pkb::PKBRead> &pkb) override;
};
}  // namespace qps
