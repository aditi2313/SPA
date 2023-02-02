#pragma once

#include <memory>
#include <vector>

#include "Clause.h"

namespace qps {
class Query {
 public:
  inline std::vector<std::unique_ptr<Clause>> &get_clauses() {
    return clauses_;
  }

 private:
  std::vector<std::unique_ptr<Clause>> clauses_;
};
}  // namespace qps
