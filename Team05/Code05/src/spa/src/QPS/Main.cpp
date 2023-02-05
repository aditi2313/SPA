#include "Main.h"

#include "QPS/preprocessor/Parser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/Evaluator.h"
#include "QPS/evaluator/Formatter.h";

namespace qps {

void Main::evaluate(std::string query, std::list<std::string> &results) {
  Parser parser;
  Query query_object = parser.ParseQuery(query);

  Validator validator;
  //TODO(Sarthak): something like validator.validate(query_object) here

  Evaluator evaluator;
  QueryResult result = evaluator.EvaluateQuery(query_object);

  Formatter formatter;
  results = formatter.FormatQuery(result);
}

}