#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>

#include "Argument.h"
#include "PKB/PKBRead.h"
#include "QueryResult.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  Clause(ArgumentPtr arg1, ArgumentPtr arg2) : arg1(std::move(arg1)), arg2(std::move(arg2)) {}

  virtual QueryResult Evaluate(std::unique_ptr<pkb::PKBRead> pkb) = 0;
  virtual ~Clause() = 0;

  bool operator==(Clause const &other) const {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);

    return ti1 == ti2 && *arg1 == *other.arg1 && *arg2 == *other.arg2;
  }

  inline bool operator!=(Clause const &other) const {
    return !(*this == other);
  }

  // Evaluating this clause returns only TRUE or FALSE
  // instead of a list of results
  inline bool IsExact() {
    return arg1->IsExact() && arg2->IsExact();
  }

  inline bool HasWildcard() {
    return arg1->IsWildcard() || arg2->IsWildcard();
  }

  inline ArgumentPtr get_arg1() { return std::move(arg1); }
  inline ArgumentPtr get_arg2() { return std::move(arg2); }

 protected:
  ArgumentPtr arg1;
  ArgumentPtr arg2;
};

// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  QueryResult Evaluate(std::unique_ptr<pkb::PKBRead> pkb) override;
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2) : Clause(std::move(arg1), std::move(arg2)) {}
};

class PatternClause : public Clause {
 public:
  QueryResult Evaluate(std::unique_ptr<pkb::PKBRead> pkb) override;
  PatternClause(ArgumentPtr arg1, ArgumentPtr arg2) : Clause(std::move(arg1), std::move(arg2)) {}
};

using ClausePtr = std::unique_ptr<Clause>;
}  // namespace qps
