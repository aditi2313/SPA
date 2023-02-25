#include "Clause.h"

#include <string>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/preprocessor/ClauseValidator.h"
#include "SP/SourceProcessor.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"
using namespace filter;  // NOLINT

namespace qps {
ClausePtr Clause::CreateClause(EntityName rel_ref_ident, ArgumentPtr arg1,
                               ArgumentPtr arg2) {
  ClauseValidator::ValidateClauseArgumentTypes(rel_ref_ident, arg1, arg2);
  if (rel_ref_ident == PQL::kModifiesRelId) {
    return std::make_unique<ModifiesClause>(std::move(arg1), std::move(arg2));
  }
  if (rel_ref_ident == PQL::kPatternRelId) {
    return std::make_unique<PatternClause>(std::move(arg1), std::move(arg2));
  }
  if (rel_ref_ident == PQL::kFollowsRelId) {
    return std::make_unique<FollowsClause>(std::move(arg1), std::move(arg2));
  }
  if (rel_ref_ident == PQL::kFollowsTRelId) {
    return std::make_unique<FollowsTClause>(std::move(arg1), std::move(arg2));
  }
  if (rel_ref_ident == PQL::kParentRelId) {
    return std::make_unique<ParentClause>(std::move(arg1), std::move(arg2));
  }
  if (rel_ref_ident == PQL::kParentTRelId) {
    return std::make_unique<ParentTClause>(std::move(arg1), std::move(arg2));
  }
  if (rel_ref_ident == PQL::kUsesRelId) {
    return std::make_unique<UsesClause>(std::move(arg1), std::move(arg2));
  }
  throw PqlSyntaxErrorException("Unknown relationship in PQL query");
}

template<class Data>
EntitySet Clause::Index(
    const Entity &index,
    std::function
        <std::unique_ptr<pkb::IndexableTable<Data>>(int)> pkb_read_function,
    std::function<void(EntitySet &, Data)> add_function
) {
  EntitySet result;
  int line = index.get_int();
  auto pkb_res = pkb_read_function(line);
  if (pkb_res->empty()) return result;
  Data data = pkb_res->get_row(line);
  add_function(result, data);
  return result;
}

EntitySet ModifiesClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::ModifiesData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<ModifiesIndexFilter>(line);
        return std::move(pkb->Modifies(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::ModifiesData data) {
        for (auto var : data.get_variables()) {
          result.insert(Entity(var));
        }
      });
}

EntitySet FollowsClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::FollowsData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<FollowsIndexFilter>(line);
        return std::move(pkb->Follows(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::FollowsData data) {
        result.insert(Entity(data.get_follows()));
      });
}

EntitySet FollowsTClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::FollowsData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<FollowsIndexFilter>(line);
        return std::move(pkb->Follows(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::FollowsData data) {
        for (auto stmt : data.get_follows_list()) {
          result.insert(Entity(stmt));
        }
      });
}

EntitySet ParentClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::ParentData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<ParentIndexFilter>(line);
        return std::move(pkb->Parent(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::ParentData data) {
        for (auto child : data.get_direct_children()) {
          result.insert(Entity(child));
        }
      });
}

EntitySet ParentTClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::ParentData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<ParentIndexFilter>(line);
        return std::move(pkb->Parent(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::ParentData data) {
        for (auto child : data.get_all_children()) {
          result.insert(Entity(child));
        }
      });
}

EntitySet UsesClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::UsesData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<UsesIndexFilter>(line);
        return std::move(pkb->Uses(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::UsesData data) {
        for (auto child : data.get_variables()) {
          result.insert(Entity(child));
        }
      });
}

EntitySet PatternClause::Filter(
    const Entity &index, const EntitySet &RHS_filter_values,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntitySet result;

  int line = index.get_int();

  std::unique_ptr<AssignPredicateFilter> filter;

  auto expr_arg = dynamic_cast<ExpressionArg *>(arg2_.get());
  auto AST = sp::SourceProcessor::ParseExpression(expr_arg->get_expression());

  filter = std::make_unique<AssignPredicateFilter>([&](pkb::AssignData data) {
    return data.get_line() == line &&
        data.TestExpression(AST, expr_arg->is_exact());
  });

  auto pkb_res = pkb->Assigns(std::move(filter))->get_result();
  if (pkb_res->empty()) return result;

  result.insert(Entity(line));

  return result;
}

EntitySet PatternClause::Index(
    const Entity &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::AssignData>(
      index,
      [&](int line) {
        auto filter = std::make_unique<AssignIndexFilter>(line);
        return std::move(pkb->Assigns(std::move(filter))->get_result());
      },
      [&](EntitySet &result, pkb::AssignData data) {
        result.insert(Entity(data.get_line()));
      });
}

Clause::~Clause() = default;
}  // namespace qps
