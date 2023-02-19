#include "Clause.h"

#include <string>
#include <utility>

#include "QPS/models/PQL.h"
#include "SP/SourceProcessor.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"
using namespace filter;  // NOLINT

namespace qps {
ClausePtr Clause::CreateClause(EntityName rel_ref_ident, ArgumentPtr arg1,
                               ArgumentPtr arg2) {
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

template <class Data>
EntityPtrList Clause::Index(
    IntEntity *index,
    std::function
        <std::unique_ptr<pkb::IndexableTable<Data>>(int)> pkb_read_function,
    std::function<void(EntityPtrList&, Data)> add_function
) {
  EntityPtrList result;
  int line = index->get_number();
  auto pkb_res = pkb_read_function(line);
  if (pkb_res->empty()) return result;
  Data data = pkb_res->get_row(line);
  add_function(result, data);
  return result;
}

EntityPtrList ModifiesClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::ModifiesData>(
    dynamic_cast<IntEntity *>(index.get()),
    [&](int line) {
      auto filter = std::make_unique<ModifiesIndexFilter>(line);
      return std::move(pkb->Modifies(std::move(filter))->get_result());
      },
    [&](EntityPtrList &result, pkb::ModifiesData data) {
      for (auto var : data.get_variables()) {
        result.push_back(factory->CreateInstance(RHS(), var));
      }
    });
}

EntityPtrList FollowsClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::FollowsData>(
      dynamic_cast<IntEntity *>(index.get()),
      [&](int line) {
        auto filter = std::make_unique<FollowsIndexFilter>(line);
        return std::move(pkb->Follows(std::move(filter))->get_result());
      },
      [&](EntityPtrList &result, pkb::FollowsData data) {
        result.push_back(factory->CreateInstance(RHS(), data.get_follows()));
      });
}

EntityPtrList FollowsTClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::FollowsData>(
      dynamic_cast<IntEntity *>(index.get()),
      [&](int line) {
        auto filter = std::make_unique<FollowsIndexFilter>(line);
        return std::move(pkb->Follows(std::move(filter))->get_result());
      },
      [&](EntityPtrList &result, pkb::FollowsData data) {
        for (auto stmt : data.get_follows_list()) {
          result.push_back(factory->CreateInstance(RHS(), stmt));
        }
      });
}

EntityPtrList ParentClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::ParentData>(
      dynamic_cast<IntEntity *>(index.get()),
      [&](int line) {
        auto filter = std::make_unique<ParentIndexFilter>(line);
        return std::move(pkb->Parent(std::move(filter))->get_result());
      },
      [&](EntityPtrList &result, pkb::ParentData data) {
        for (auto child : data.get_direct_children()) {
          result.push_back(factory->CreateInstance(RHS(), child));
        }
      });
}

EntityPtrList ParentTClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::ParentData>(
      dynamic_cast<IntEntity *>(index.get()),
      [&](int line) {
        auto filter = std::make_unique<ParentIndexFilter>(line);
        return std::move(pkb->Parent(std::move(filter))->get_result());
      },
      [&](EntityPtrList &result, pkb::ParentData data) {
        for (auto child : data.get_all_children()) {
          result.push_back(factory->CreateInstance(RHS(), child));
        }
      });
}

EntityPtrList UsesClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::UsesData>(
      dynamic_cast<IntEntity *>(index.get()),
      [&](int line) {
        auto filter = std::make_unique<UsesIndexFilter>(line);
        return std::move(pkb->Uses(std::move(filter))->get_result());
      },
      [&](EntityPtrList &result, pkb::UsesData data) {
        for (auto child : data.get_variables()) {
          result.push_back(factory->CreateInstance(RHS(), child));
        }
      });
}

EntityPtrList PatternClause::Filter(
    const EntityPtr &index, const EntityPtrList &RHS_filter_values,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;

  IntEntity *line_arg = dynamic_cast<IntEntity *>(index.get());
  int line = line_arg->get_number();

  std::unique_ptr<AssignPredicateFilter> filter;

  auto expr_arg = dynamic_cast<ExpressionArg *>(arg2_.get());
  auto AST = sp::SourceProcessor::ParseExpression(expr_arg->get_expression());

  filter = std::make_unique<AssignPredicateFilter>([&](pkb::AssignData data) {
    return data.get_line() == line &&
           data.TestExpression(AST, expr_arg->is_exact());
  });

  auto pkb_res = pkb->Assigns(std::move(filter))->get_result();
  if (pkb_res->empty()) return result;

  result.push_back(factory->CreateInstance(PQL::kAssignEntityName, line));

  return result;
}

EntityPtrList PatternClause::Index(
    const EntityPtr &index, const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  return Clause::Index<pkb::AssignData>(
      dynamic_cast<IntEntity *>(index.get()),
      [&](int line) {
        auto filter = std::make_unique<AssignIndexFilter>(line);
        return std::move(pkb->Assigns(std::move(filter))->get_result());
      },
      [&](EntityPtrList &result, pkb::AssignData data) {
        result.push_back(factory->CreateInstance(RHS(), data.get_line()));
      });
}

Clause::~Clause() = default;
}  // namespace qps
