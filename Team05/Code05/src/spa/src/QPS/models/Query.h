#pragma once

#include <vector>
#include "Clause.h"

namespace qps {
class Query {
 public:
  inline std::vector<Clause *> get_clauses() {
    return clauses_;
  }
 private:
  std::vector<Clause *> clauses_;
};
}  // namespace qps

