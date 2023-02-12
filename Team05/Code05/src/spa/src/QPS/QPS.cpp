#include <memory>
#include <utility>

#include "QPS.h"

#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/Evaluator.h"
#include "QPS/evaluator/Formatter.h"

namespace qps {
// Called in TestWrapper
void QPS::evaluate(std::string query, std::list<std::string> &results) {
  SelectClParser parser;
  std::unique_ptr<Query> query_object = parser.ParseQuery(query);

  Validator validator;
  // TODO(Sarthak): something like validator.validate(query_object) here

  Evaluator evaluator;
  ListQueryResultPtr result = evaluator.EvaluateQuery(query_object);

  Formatter formatter;
  results = formatter.FormatQuery(result);
}

// Used for integration tests
std::unique_ptr<pkb::PKBRead> QPS::evaluate(
    std::string query,
    std::list<std::string> &results,
    std::unique_ptr<pkb::PKBRead> &pkb) {
  SelectClParser parser;
  std::unique_ptr<Query> query_object = parser.ParseQuery(query);

  Validator validator;
  // TODO(Sarthak): something like validator.validate(query_object) here

  Evaluator evaluator;
  evaluator.inject_pkb(pkb);  // Inject testing PKB here
  ListQueryResultPtr result = evaluator.EvaluateQuery(query_object);

  Formatter formatter;
  results = formatter.FormatQuery(result);
  return std::move(pkb);
}
}  // namespace qps
