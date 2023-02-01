#pragma once

#include "Argument.h"
#include "QueryResult.h"
#include "PKB/PKBStub.h"

namespace qps {
// Pure abstract base class:
// cannot be instantiated as its own object.
class Clause {
 public:
  virtual QueryResult Evaluate(pkb::PKBStub &pkb) = 0;

 private:
  Argument arg1;
  Argument arg2;

};

class ModifiesClause : Clause {
  QueryResult Evaluate(pkb::PKBStub &pkb) override;
};
}

