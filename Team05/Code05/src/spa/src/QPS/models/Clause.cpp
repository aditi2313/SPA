#include <utility>
#include <string>

#include "Clause.h"
#include "PKB/data/ModifiesData.h"
#include "SP/Parser.h"
#include "common/filter/filters/AssignFilter.h"

using namespace filter;  // NOLINT

namespace qps {
QueryResult ModifiesClause::Evaluate(const std::unique_ptr<pkb::PKBRead>& pkb) {
  // TODO(Gab): setup arguement to evaluate the filter.

  // CURRENTLY this only works for Modifies( statement number, variable )
  // TODO(JL): generalize this to work for more types of
  // Modifies clauses
  QueryResult query_result;

  int line = std::stoi(arg1.get_arg());

  auto filter = std::make_unique<ModifiesFilterByLine>(line);
  auto result = pkb->Modifies(std::move(filter));
  
  
  
  auto res = result->get_result();
  if (!res->exists(line)) {
    return query_result;
  }
  auto data = result->get_result()->get_row(line);
  
  for (auto var : data.get_variables()) {
    query_result.add_query_result(models::EntityStub(var));
  }

  return query_result;
}
QueryResult PatternClause::Evaluate(const std::unique_ptr<pkb::PKBRead>& pkb) {
  QueryResult query_result;

  // preprocess expression string to insert whitespace
  std::string expression = "";
  for (char c : arg2.get_arg()) {
    if (c == '+' || c == '-') {
      expression += " " + std::string(1, c) + " ";
    } else {
      expression += c;
    }
  }

  auto ASTNode = sp::Parser::ParseExpr(expression);
  auto filter = std::make_unique<AssignFilterByExpression>(std::move(ASTNode));
  auto result = pkb->Assigns(std::move(filter));

  auto data = result->get_result()->get_indexes();

  for (auto var : data) {
    query_result.add_query_result(models::EntityStub(std::to_string(var)));
  }

  return query_result;
}

Clause::~Clause() = default;
}  // namespace qps
