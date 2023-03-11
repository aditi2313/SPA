#pragma once

#include "Clause.h"
#include "common/filter/filters/IndexFilter.h"

using filter::AssignIndexFilter;
using filter::AssignPredicateFilter;

namespace qps {
// RS between a statement and a list of variables
class PatternClause : public Clause {
 public:
  PatternClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kPatternRelName;
  }

  inline void Index(
      const Entity &index,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    Clause::Index<pkb::AssignData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<AssignIndexFilter>(key);
          return std::move(pkb->Assigns(std::move(filter))->get_result());
        },
        [&](EntitySet &result, pkb::AssignData data) {
          result.insert(Entity(data.get_index()));
        },
        results);
  }

  inline void Filter(
      const Entity &index,
      const EntitySet &RHS_filter_values,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    int line = index.get_int();
    std::unique_ptr<AssignPredicateFilter> filter;

    auto expr_arg = dynamic_cast<ExpressionArg *>(arg2_.get());
    auto &AST = expr_arg->get_expression();

    filter = std::make_unique<AssignPredicateFilter>([&](pkb::AssignData data) {
      return data.get_index() == line &&
          data.TestExpression(AST, expr_arg->is_exact());
    });

    auto pkb_res = pkb->Assigns(std::move(filter))->get_result();
    if (pkb_res->empty()) return;

    results.insert(Entity(line));
  }
};

}  // namespace qps
