#include <memory>
#include <utility>

#include "QPS.h"

#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/QueryEvaluator.h"
#include "QPS/factories/Export.h"

namespace qps {
MasterArgumentFactory master_argument_factory_;
MasterClauseFactory master_clause_factory_;
MasterEntityFactory master_entity_factory_;

void QPS::evaluate(
    std::string query,
    std::list<std::string> &results,
    pkb::PKBReadPtr &pkb) {
  try {
    SelectClParser parser;
    std::unique_ptr<Query> query_object = parser.ParseQuery(query);
    Validator::Validate(query_object);

    QueryEvaluator evaluator(pkb);
    QueryResultPtr result = evaluator.EvaluateQuery(query_object);

    result->Format(results);
  } catch (PqlSyntaxErrorException e) {
    results = {"SyntaxError"};
  } catch (PqlSemanticErrorException e) {
    results = {"SemanticError"};
  }
}
}  // namespace qps
