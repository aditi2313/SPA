#include "Clause.h"

#include <string>
#include <utility>

#include "SP/SourceProcessor.h"
#include "QPS/evaluator/TableJoiner.h"
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
    EntitySet &results) {
  Clause::Index<pkb::CallsData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<CallsIndexFilter>(key);
        return std::move(pkb->Calls(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::CallsData data) {
        for (auto child : data.get_total_calls()) {
          result.insert(Entity(child));
        }
      },
      results);
}

void NextClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  Clause::Index<pkb::NextData>(
      index,
      [&](Entity::Value key) {
        auto filter = std::make_unique<NextIndexFilter>(key);
        return std::move(pkb->Next(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::NextData data) {
        for (auto child : data.get_next_im_list()) {
          result.insert(Entity(child));
        }
      },
      results);
}

void WithClause::Preprocess(
    const pkb::PKBReadPtr &pkb,
    Table &query_table) {
  InitializeSynonymAttrValue(arg1_, pkb, query_table);
  InitializeSynonymAttrValue(arg2_, pkb, query_table);
}

void WithClause::InitializeSynonymAttrValue(
    ArgumentPtr &arg,
    const pkb::PKBReadPtr &pkb,
    Table &query_table) {
  if (!arg->IsSynonym()) return;
  SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
  bool is_secondary_attr_value =
      syn_arg->is_secondary_attr_ref();

  // Update query_table with rows mapping from
  // Index to AttrValue
  // e.g. calls (line) to calls (procName)
  EntitySet indexes;
  syn_arg->InitializeEntities(
      query_table, pkb, indexes, false);
  Table::TwoSynonymRows rows;

  for (auto &index : indexes) {
    if (is_secondary_attr_value) {
      rows.emplace_back(index, syn_arg->get_secondary_attr_value(pkb, index));
    } else {
      rows.emplace_back(index, index);
    }
  }

  std::vector<SynonymName> columns;
  SynonymName col1 = syn_arg->get_syn_name();
  SynonymName col2 = syn_arg->get_full_name();
  columns.emplace_back(col1);
  columns.emplace_back(col2);
  Table new_table(columns);

  new_table.add_values(col1, col2, rows);

  query_table = TableJoiner::Join(query_table, new_table);
}

void WithClause::Index(
    const Entity &index,
    const pkb::PKBReadPtr &pkb,
    EntitySet &results) {
  // Just return itself
  results.insert(index);
}

Clause::~Clause() = default;
}  // namespace qps
