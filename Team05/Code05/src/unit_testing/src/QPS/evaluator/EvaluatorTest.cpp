#include "catch.hpp"
#include "QPS/evaluator/Evaluator.h"

using namespace qps;

// TODO: replace with real unit tests after PKB and parser is implemented
TEST_CASE("Test QueryEvaluator") {
  Evaluator query_evaluator;

  SECTION("One such-that clause") {
    query_evaluator.EvaluateQuery(Query());
    REQUIRE(true);
  };
}