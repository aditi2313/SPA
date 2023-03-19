#include <catch.hpp>

#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/preprocessor/Validator.h"
#include "QPS/evaluator/ClauseOptimiser.h"

using namespace qps;  // NOLINT

// Helper method for testing
QueryPtr BuildQuery(std::string query_str) {
  SelectClParser parser;
  QueryPtr query = parser.ParseQuery(query_str);
  Validator::Validate(query);
  return query;
}

TEST_CASE("Test ClauseOptimiser GroupClauses for clauses in one group") {
  // First example given in take-home homework
  std::string query_str = "assign a1, a2, a3; "
                          "stmt s1, s2, s3; "
                          "variable v1, v2, v3; "
                          "Select <s1, s2, v2> such that "
                          "Uses(s3, v1) and "         // 0
                          "Modifies(s3, \"x\") and "  // 1
                          "Follows(s1, s2) and "      // 2
                          "Parent(s3, s1) and "       // 3
                          "Uses(s2, v1)";             // 4

  QueryPtr query = BuildQuery(query_str);
  std::vector<ClauseOptimiser::Group> actual_groups =
      ClauseOptimiser::GroupClauses(query->get_clauses());

  // This order of evaluation of the clauses ensures that
  // there is always a shared synonym in the current query_table
  // as compared to {0, 1, 2, 3, 4}
  std::vector<ClauseOptimiser::Group> expected_groups = {
      {0, 1, 3, 4, 2}
  };

  REQUIRE(actual_groups == expected_groups);
}

TEST_CASE("Test ClauseOptimiser GroupClauses for clauses in multiple group") {
  // Second example given in take-home homework
  std::string query_str = "assign a, a1, a2; "
                          "stmt s1, s2, s3; "
                          "variable v1, v2; "
                          "Select <s1, a, a1, v2> such that "
                          "Uses(5, \"y\") and "        // 0
                          "Uses(s1, v1) and "          // 1
                          "Affects(a1, a2) "           // 2
                          "with a1.stmt# = 20 "        // 3
                          "such that Parent(s1, s2) "  // 4
                          "pattern a2(\"a\", _) "      // Modifies(a2, "a") is 5
                                                       // pattern(a2, _) is 6
                          "such that Next(s2, s3) "    // 7
                          "and Modifies(s1, \"x\") "   // 8
                          "and Modifies(a, v2) "       // 9
                          "pattern a(v1, \"x\")";      // Modifies(a, v1) is 10
                                                       // pattern(a, v1) is 11

  QueryPtr query = BuildQuery(query_str);
  std::vector<ClauseOptimiser::Group> actual_groups =
      ClauseOptimiser::GroupClauses(query->get_clauses());

  std::vector<ClauseOptimiser::Group> expected_groups = {
      {0},
      {1, 4, 8, 10, 7, 9, 11},
      {2, 3, 5, 6}
  };

  REQUIRE(actual_groups == expected_groups);
}
