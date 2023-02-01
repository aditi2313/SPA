#pragma once

#include "Argument.h"
#include "QueryResult.h"
#include "PKB/PKBStub.h"

namespace qps {
// Abstract class - cannot be instantiated
// as its own object.
class Clause {
 private:
  Argument arg1;
  Argument arg2;

 public:
  virtual QueryResult Evaluate(pkb::PKBStub &pkb) = 0;
};

class ModifiesClause : Clause {
  QueryResult Evaluate(pkb::PKBStub &pkb) override;
};
}

