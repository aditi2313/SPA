#include "Clause.h"
#include "PKB/data/ModifiesData.h"

using namespace filter;  // NOLINT

namespace qps {
QueryResult ModifiesClause::Evaluate(std::unique_ptr<pkb::PKBRead> pkb) {
  // TODO(Gab): setup arguement to evaluate the filter.

  // TODO(JL): generalize this to work for more types of
  // Modifies clauses
  QueryResult query_result;

  int line = std::stoi(arg1.get_arg());

  auto filter = std::make_unique<ModifiesFilterByLine>(line);
  auto result = pkb->Modifies(std::move(filter));

//  auto data = result->get_result()->get_row(line);
//  for (auto var : data.get_variables()) {
//    query_result.add_query_result(models::EntityStub(var));
//  }

  return query_result;
}
QueryResult PatternClause::Evaluate(std::unique_ptr<pkb::PKBRead> pkb) {
  // TODO(jl): replace with pattern method
  // return pkb->ModifiesStub();
  throw new NotImplementedException();
}

Clause::~Clause() = default;
}  // namespace qps
