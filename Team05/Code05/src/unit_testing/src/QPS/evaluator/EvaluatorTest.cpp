#include <catch.hpp>

#include "QPS/evaluator/Evaluator.h"

using namespace qps;  // NOLINT

// TODO(JL): replace with real unit tests after PKB and parser is implemented
TEST_CASE("Test QueryEvaluator") {
  Evaluator query_evaluator;

  SECTION("One such-that clause") {
    REQUIRE(true);
  };
}
