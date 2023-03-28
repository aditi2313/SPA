#pragma once

#include <memory>
#include <utility>

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::AssignIndexFilter;
using filter::AssignPredicateFilter;

namespace qps {
// RS between a statement and a list of variables
class PatternAssignClause : public Clause {
 public:
  PatternAssignClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(
      ClauseType::kPatternAssign, std::move(arg1), std::move(arg2)) {}

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    AssignIndexFilter filter(index.get_value());
    auto& reader = pkb->Assigns(filter);
    if (reader.reached_end()) return;
    auto &data = reader.read_data();
    results.insert(Entity(data.get_index()));
    
  }

  inline void Filter(
      const Entity &index,
      const EntitySet &RHS_filter_values,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    int line = index.get_int();    

    auto expr_arg = dynamic_cast<ExpressionArg *>(arg2_.get());
    auto &AST = expr_arg->get_expression();

    AssignPredicateFilter filter([&](pkb::AssignData data) {
      return data.get_index() == line &&
          data.TestExpression(AST, expr_arg->is_exact());
    });

    auto &result = pkb->Assigns(filter);
    if (result.reached_end()) return;

    results.insert(Entity(line));
  }
};

}  // namespace qps
