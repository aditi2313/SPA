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
  QueryResultPtr result = evaluator.EvaluateQuery(std::move(query_object));

  Formatter formatter;
  results = formatter.FormatQuery(std::move(result));
}

// Used for integration tests
void QPS::evaluate(
    std::string query,
    std::list<std::string> &results,
    std::unique_ptr<pkb::PKBRead> &pkb) {
  Parser parser;
  std::unique_ptr<Query> query_object = parser.ParseQuery(query);

  Validator validator;
  // TODO(Sarthak): something like validator.validate(query_object) here

  Evaluator evaluator;
  evaluator.inject_pkb(pkb);  // Inject testing PKB here
  QueryResultPtr result = evaluator.EvaluateQuery(std::move(query_object));

  Formatter formatter;
  results = formatter.FormatQuery(std::move(result));
}
}  // namespace qps