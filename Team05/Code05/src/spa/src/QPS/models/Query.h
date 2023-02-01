#pragma once

#include <vector>
#include "Clause.h"

namespace qps {
class Query {
 private:
  std::vector<Clause *> clauses_;
 public:
  std::vector<Clause *> GetClauses() {
    return clauses_;
  }
};
}  // namespace qps

