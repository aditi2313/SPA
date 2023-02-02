#pragma once

#include <memory>

#include "Argument.h"
#include "models/results/QueryResult.h"
#include "PKB/PKBRead.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  virtual models::QueryResult Evaluate(std::unique_ptr<pkb::PKBRead> &pkb) = 0;

 private:
  Argument arg1;
  Argument arg2;
};

class ModifiesClause : Clause {
  models::QueryResult Evaluate(std::unique_ptr<pkb::PKBRead> &pkb) override;
};
}  // namespace qps

