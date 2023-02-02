#pragma once

#include <memory>

#include "Argument.h"
#include "QueryResult.h"
#include "PKB/PKBStub.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  virtual QueryResult Evaluate(std::unique_ptr<pkb::PKBStub> pkb) = 0;
  virtual ~Clause() = 0;

 private:
  Argument arg1;
  Argument arg2;
};

class ModifiesClause : public Clause {
 public:
  QueryResult Evaluate(std::unique_ptr<pkb::PKBStub> pkb) override;
};
}  // namespace qps

