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
  Clause(Argument arg1, Argument arg2) : arg1(arg1), arg2(arg2) {}

  virtual QueryResult Evaluate(std::unique_ptr<pkb::PKBStub> pkb) = 0;
  virtual ~Clause() = 0;

 protected:
  Argument arg1;
  Argument arg2;
};

class ModifiesClause : public Clause {
 public:
  QueryResult Evaluate(std::unique_ptr<pkb::PKBStub> pkb) override;
  ModifiesClause(Argument arg1, Argument arg2) : Clause(arg1, arg2) {}
  bool operator==(ModifiesClause const &other) const {
    return arg1 == other.arg1 && arg2 == other.arg2;
  }
};

class PatternClause : public Clause {
 public:
  QueryResult Evaluate(std::unique_ptr<pkb::PKBStub> pkb) override;
  PatternClause(Argument arg1, Argument arg2) : Clause(arg1, arg2) {}
  bool operator==(PatternClause const &other) const {
    return arg1 == other.arg1 && arg2 == other.arg2;
  }
};
}  // namespace qps

