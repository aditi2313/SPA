#pragma once

#include <utility>
#include <unordered_set>
#include <memory>

#include "Argument.h"

namespace qps {
class ExpressionArg : public Argument {
 public:
  explicit ExpressionArg(sp::ExprNodePtr expr, bool is_exact)
      : Argument(), expr_(std::move(expr)), is_exact_(is_exact) {}

  inline bool IsExpression() override { return true; }
  inline sp::ExprNodePtr &get_expression() { return expr_; }
  inline bool is_exact() { return is_exact_; }

  inline bool Validate(
      std::unordered_set<EntityName> &entity_names) override {
    return true;
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    return;
  }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Expr Arg: " << expr_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<ExpressionArg>(
        expr_->Copy(), is_exact_);
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    auto arg = dynamic_cast<ExpressionArg *>(&other);
    return expr_->DeepEquals(*(arg->expr_))
        && is_exact_ == arg->is_exact_;
  }

 private:
  sp::ExprNodePtr expr_;  // Expression
  bool is_exact_;
};
}  // namespace qps
