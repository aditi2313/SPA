#include <memory>
#include <utility>

#include "QPS.h"

#include "QPS/preprocessor/Parser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/Evaluator.h"
#include "QPS/evaluator/Formatter.h"

namespace qps {
// Called in TestWrapper
void QPS::evaluate(std::string query, std::list<std::string> &results) {
  Parser parser;
  std::unique_ptr<Query> query_object = parser.ParseQuery(query);

  Validator validator;
  // TODO(Sarthak): something like validator.validate(query_object) here

  Evaluator evaluator;
  QueryResultPtr result = evaluator.EvaluateQuery(query_object);

  Formatter formatter;
  results = formatter.FormatQuery(result);
}

// Used for integration tests
std::unique_ptr<pkb::PKBRead> QPS::evaluate(
    std::string query,
    std::list<std::string> &results,
    std::unique_ptr<pkb::PKBRead> &pkb) {
  Parser parser;
  std::unique_ptr<Query> query_object = parser.ParseQuery(query);

  Validator validator;
  // TODO(Sarthak): something like validator.validate(query_object) here

  Evaluator evaluator;
  evaluator.inject_pkb(pkb);  // Inject testing PKB here
  QueryResultPtr result = evaluator.EvaluateQuery(query_object);

  Formatter formatter;
  results = formatter.FormatQuery(result);
  return evaluator.retrieve_pkb();
}
}  // namespace qps
