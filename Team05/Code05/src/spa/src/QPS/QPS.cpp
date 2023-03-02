#include <memory>
#include <utility>

#include "QPS.h"

#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/QueryEvaluator.h"
#include "QPS/evaluator/Formatter.h"

namespace qps {
// Used for integration tests
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

    Formatter formatter;
    results = formatter.FormatQuery(result);
  } catch (PqlSyntaxErrorException e) {
    results = {"SyntaxError"};
  } catch (PqlSemanticErrorException e) {
    results = {"SemanticError"};
  }
}
}  // namespace qps
