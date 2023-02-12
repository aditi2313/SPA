#include <string>
#include <utility>

#include "Clause.h"
#include "QPS/models/PQL.h"
#include "SP/lexer/Lexer.h"
#include "SP/parser/expression/ExpressionParser.h"
#include "common/filter/filters/AssignFilter.h"

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
  throw PqlSyntaxErrorException("Unknown relationship in PQL query");
}

QueryResultPtr ModifiesClause::Evaluate(
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {

  ListQueryResultPtr query_result = std::make_unique<ListQueryResult>();

  IntegerArg *line_arg = reinterpret_cast<IntegerArg *>(arg1.get());
  int line = line_arg->get_number();

  auto filter = std::make_unique<ModifiesFilterByLine>(line);
  auto pkb_res = pkb->Modifies(std::move(filter))->get_result();

  if (!pkb_res->exists(line)) return query_result;

  auto data = pkb_res->get_row(line);
  for (auto var : data.get_variables()) {
    query_result->add_query_result(
        factory->CreateInstance(PQL::kVariableEntityId, var));
  }

  return query_result;
}
QueryResultPtr PatternClause::Evaluate(
    const std::unique_ptr<MasterEntityFactory> &factory,
    const std::unique_ptr<pkb::PKBRead> &pkb) {
  // TODO(JL): generalize this to work for more types of
  // Pattern clauses

  ListQueryResultPtr query_result = std::make_unique<ListQueryResult>();

//   preprocess expression string to insert whitespace
  std::string expression = "";
  ExpressionArg *expr_arg = reinterpret_cast<ExpressionArg *> (arg2.get());
  for (char c : expr_arg->get_expression()) {
    if (c == '+' || c == '-') {
      expression += " " + std::string(1, c) + " ";
    } else {
      expression += c;
    }
  }

  sp::Lexer lxr(expression);
  sp::ExpressionParser exp_parser;
  auto ASTNode = exp_parser.parse(lxr);
  auto filter = std::make_unique<AssignFilterByExpression>(std::move(ASTNode));
  auto result = pkb->Assigns(std::move(filter));

  auto data = result->get_result()->get_indexes();

  for (auto a : data) {
    query_result->add_query_result(
        factory->CreateInstance(PQL::kAssignEntityId, a));
  }

  return query_result;
}

Clause::~Clause() = default;
}  // namespace qps
