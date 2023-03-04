#include "Clause.h"

#include <string>
#include <utility>

#include "SP/SourceProcessor.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"
using namespace filter;  // NOLINT

namespace qps {
template<class Data>
void Clause::Index(
    const Entity &index,
    std::function
        <std::unique_ptr<pkb::IndexableTable<Data>>(
            Entity::Value)> pkb_read_function,
    std::function<void(EntitySet &, Data)> add_function,
    EntitySet &results) {
  Entity::Value key = index.get_value();
  auto pkb_res = pkb_read_function(key);
  if (pkb_res->empty()) return;
  Data data = pkb_res->get_row(key);
  add_function(results, data);
}

void ModifiesClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::ModifiesData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<ModifiesIndexFilter>(key);
        return std::move(pkb->Modifies(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::ModifiesData data) {
        for (auto var : data.get_variables()) {
          result.insert(Entity(var));
        }
      },
      results);
}

void FollowsClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::FollowsData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<FollowsIndexFilter>(key);
        return std::move(pkb->Follows(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::FollowsData data) {
        result.insert(Entity(data.get_follows()));
      },
      results);
}

void FollowsTClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::FollowsData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<FollowsIndexFilter>(key);
        return std::move(pkb->Follows(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::FollowsData data) {
        for (auto stmt : data.get_follows_list()) {
          result.insert(Entity(stmt));
        }
      },
      results);
}

void ParentClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::ParentData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<ParentIndexFilter>(key);
        return std::move(pkb->Parent(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::ParentData data) {
        for (auto child : data.get_direct_children()) {
          result.insert(Entity(child));
        }
      },
      results);
}

void ParentTClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::ParentData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<ParentIndexFilter>(key);
        return std::move(pkb->Parent(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::ParentData data) {
        for (auto child : data.get_all_children()) {
          result.insert(Entity(child));
        }
      },
      results);
}

void UsesClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::UsesData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<UsesIndexFilter>(key);
        return std::move(pkb->Uses(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::UsesData data) {
        for (auto child : data.get_variables()) {
          result.insert(Entity(child));
        }
      },
      results);
}

void PatternClause::Filter(
    const Entity &index,
    const EntitySet &RHS_filter_values,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {

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

void PatternClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
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

void CallsClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::CallsData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<CallsIndexFilter>(key);
        return std::move(pkb->Calls(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::CallsData data) {
        for (auto child : data.get_direct_calls()) {
          result.insert(Entity(child));
        }
      },
      results);
}

void CallsTClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {}

Clause::~Clause() = default;
}  // namespace qps
