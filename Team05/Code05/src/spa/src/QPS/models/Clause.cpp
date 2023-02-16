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
  if (rel_ref_ident == PQL::kParentlId) {
      return std::make_unique<Uses
  }
  throw PqlSyntaxErrorException("Unknown relationship in PQL query");
}

EntityPtrList ModifiesClause::Index(
    const EntityPtr &index,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;
  IntEntity *line_arg = dynamic_cast<IntEntity*>(index.get());
  int line = line_arg->get_number();
  auto filter = std::make_unique<ModifiesIndexFilter>(line);
  auto pkb_res = pkb->Modifies(std::move(filter))->get_result();

  if (!pkb_res->exists(line)) return result;

  auto data = pkb_res->get_row(line);
  for (auto var : data.get_variables()) {
    result.push_back(
        factory->CreateInstance(PQL::kVariableEntityName, var));
  }

  return result;
}

// TODO(JL): This method is a bit messy because it calls the
// PredicateFilter inside of a function meant for Indexing.
// Pattern is kind of tricky, will move on to
// other relationships first, then rewrite/refactor
// this method in a separate PR that also closes Issue 58.
EntityPtrList PatternClause::Index(
    const EntityPtr &index,
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  EntityPtrList result;
  IntEntity *line_arg = dynamic_cast<IntEntity*>(index.get());
  int line = line_arg->get_number();
  // Preprocess expression string to insert whitespace
  std::string expression = "";
  ExpressionArg expression_arg = dynamic_cast<ExpressionArg &>(
      *arg2_.get());
  for (char c : expression_arg.get_expression()) {
    if (c == '+' || c == '-') {
      expression += " " + std::string(1, c) + " ";
    } else {
      expression += c;
    }
  }

  EntityPtrList UsesClause::Index(
      const EntityPtr & index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) {

)

  sp::SourceProcessor source_processor;
  auto ASTNode = source_processor.ParseExpression(expression);
  auto filter = std::make_unique<AssignPredicateFilter>(
      [&](auto data) {
        return data.TestExpression(ASTNode);
      });
  auto pkb_res = pkb->Assigns(std::move(filter));
  auto data = pkb_res->get_result()->get_indexes();
  if (data.find(line) == data.end()) return result;

  for (auto a : data) {
    result.push_back(
        factory->CreateInstance(PQL::kAssignEntityName, a));
  }

  return result;
}

Clause::~Clause() = default;
}  // namespace qps
