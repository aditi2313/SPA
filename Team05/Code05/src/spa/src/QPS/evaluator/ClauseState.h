#pragma once

#include "QPS/models/clauses/Clause.h"
#include "QPS/models/Entity.h"
#include "QPS/models/Table.h"

namespace qps {
// Container class that contains the multiple references
// needed to be passed around in ClauseEvaluator functions
class ClauseState {
 public:
  ClauseState(
      ClausePtr &clause,
      Table &clause_table,
      EntitySet &LHS,
      EntitySet &RHS)
      : clause_(clause),
        clause_table_(clause_table),
        LHS_(LHS),
        RHS_(RHS) {}

  inline const ClausePtr &get_clause() {
    return clause_;
  }

  inline Table &get_clause_table() {
    return clause_table_;
  }

  inline const EntitySet &get_lhs() {
    return LHS_;
  }

  inline const EntitySet &get_rhs() {
    return RHS_;
  }

  inline EntitySet &get_lhs_results() {
    return LHS_results_;
  }

  inline EntitySet &get_rhs_results() {
    return RHS_results_;
  }

 private:
  const ClausePtr &clause_;
  Table &clause_table_;
  const EntitySet &LHS_;
  const EntitySet &RHS_;
  EntitySet LHS_results_;
  EntitySet RHS_results_;
};
}  // namespace qps
