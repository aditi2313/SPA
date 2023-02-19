#include <memory>
#include <utility>

#include "QPS.h"

#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/Evaluator.h"
#include "QPS/evaluator/Formatter.h"

namespace qps {
// Used for integration tests
std::unique_ptr<pkb::PKBRead> QPS::evaluate(
    std::string query,
    std::list<std::string> &results,
    std::unique_ptr<pkb::PKBRead> &pkb) {
  SelectClParser parser;
  std::unique_ptr<Query> query_object = parser.ParseQuery(query);

  Validator::Validate(query_object);

  Evaluator evaluator(pkb);
  QueryResultPtr result = evaluator.EvaluateQuery(query_object);

  Formatter formatter;
  results = formatter.FormatQuery(result);
  return evaluator.retrieve_pkb();
}
}  // namespace qps
