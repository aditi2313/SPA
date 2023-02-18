#include <string>
#include <utility>

#include "Clause.h"
#include "QPS/models/PQL.h"
#include "SP/SourceProcessor.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/PredicateFilter.h"

using namespace filter;  // NOLINT

namespace qps {
ClausePtr Clause::CreateClause(
    EntityName rel_ref_ident, ArgumentPtr arg1, ArgumentPtr arg2) {
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
  throw PqlSyntaxErrorException("Unknown relationship in PQL query");
}

EntityPtrList ModifiesClause::Index(
    const EntityPtr &index,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;
  IntEntity *line_arg = dynamic_cast<IntEntity *>(index.get());
  int line = line_arg->get_number();
  auto filter = std::make_unique<ModifiesIndexFilter>(line);
  auto pkb_res = pkb->Modifies(std::move(filter))->get_result();

  if (!pkb_res->exists(line)) return result;

  auto data = pkb_res->get_row(line);
  for (auto var : data.get_variables()) {
    result.push_back(
        factory->CreateInstance(RHS(), var));
  }

  return result;
}

EntityPtrList FollowsClause::Index(
    const EntityPtr &index,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;

  IntEntity *line_arg = dynamic_cast<IntEntity *>(index.get());
  int line = line_arg->get_number();
  auto filter = std::make_unique<FollowsIndexFilter>(line);
  auto pkb_res = pkb->Follows(std::move(filter))->get_result();

  if (!pkb_res->exists(line)) return result;

  auto data = pkb_res->get_row(line);
  result.push_back(factory->CreateInstance(
      RHS(), data.get_follows()));

  return result;
}

EntityPtrList FollowsTClause::Index(
    const EntityPtr &index,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;

  IntEntity *line_arg = dynamic_cast<IntEntity *>(index.get());
  int line = line_arg->get_number();
  auto filter = std::make_unique<FollowsIndexFilter>(line);
  auto pkb_res = pkb->Follows(std::move(filter))->get_result();

  if (!pkb_res->exists(line)) return result;

  auto data = pkb_res->get_row(line).get_follows_list();
  for (auto stmt : data) {
    result.push_back(factory->CreateInstance(
        PQL::kStmtEntityName, stmt));
  }

  return result;
}

EntityPtrList PatternClause::Filter(
    const EntityPtr &index,
    const EntityPtrList &RHS_filter_values,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;

  IntEntity *line_arg = dynamic_cast<IntEntity *>(index.get());
  int line = line_arg->get_number();

  std::unique_ptr<AssignPredicateFilter> filter;

  auto expr_arg = dynamic_cast<ExpressionArg *>(arg2_.get());
  auto AST =
      sp::SourceProcessor::ParseExpression(expr_arg->get_expression());

  filter = std::make_unique<AssignPredicateFilter>(
      [&](pkb::AssignData data) {
        return data.get_line() == line
            && data.TestExpression(AST, expr_arg->is_exact());
      });

  auto pkb_res = pkb->Assigns(std::move(filter))->get_result();
  if (pkb_res->empty()) return result;

  result.push_back(
      factory->CreateInstance(PQL::kAssignEntityName, line));

  return result;
}

EntityPtrList PatternClause::Index(
    const EntityPtr &index,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;
  IntEntity *line_arg = dynamic_cast<IntEntity *>(index.get());
  int line = line_arg->get_number();

  auto filter = std::make_unique<AssignIndexFilter>(line);
  auto pkb_res = pkb->Assigns(std::move(filter))->get_result();
  if (pkb_res->empty()) return result;
  result.push_back(
      factory->CreateInstance(PQL::kAssignEntityName, line));

  return result;
}


Clause::~Clause() = default;
}  // namespace qps
