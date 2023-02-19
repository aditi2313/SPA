#include <exception>
#include <catch.hpp>

#include "QPS/QPS.h"
#include "PKB/PKBWrite.h"

using namespace qps; // NOLINT
using namespace pkb; // NOLINT

// Helper method for testing
std::unique_ptr<PKBRead> CreateEmptyPKB() {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));
  return std::make_unique<PKBRead>(pkb_write.EndWrite());
}

TEST_CASE("Test queries that throw SyntaxError") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb_read = CreateEmptyPKB();
  std::list<std::string> kSyntaxErrorResult = {"SyntaxError"};

  SECTION("Query with semi-colon after Select"
          "throw PqlSyntaxErrorException") {
    // Select v should not end with a semi-clon
    std::string query_string = "variable v; Select v;";

    std::list<std::string> results;
    qps.evaluate(query_string, results, pkb_read);

    REQUIRE(results == kSyntaxErrorResult);
  }

  SECTION("Query with wrong casing in select "
          "throw PqlSyntaxErrorException") {
    // select should be Select
    std::string query_string = "variable v; select v";

    std::list<std::string> results;
    qps.evaluate(query_string, results, pkb_read);

    REQUIRE(results == kSyntaxErrorResult);
  }

  SECTION("Query with wrong order of states should "
          "throw PqlSyntaxErrorException") {
    // Pattern should not be before such-that
    std::string query_string = "variable v; procedure p; "
                               "Select v, p pattern a(_, \"x + y\") "
                               "such that Modifies(6, v)";

    std::list<std::string> results;
    qps.evaluate(query_string, results, pkb_read);

    REQUIRE(results == kSyntaxErrorResult);
  }

  SECTION("Query with wrong order of states should "
          "throw PqlSyntaxErrorException") {
    // Pattern should not be before such-that
    std::string query_string = "variable v; procedure p; "
                               "Select v, p pattern a(_, \"x + y\") "
                               "such that Modifies(6, v)";

    std::list<std::string> results;
    qps.evaluate(query_string, results, pkb_read);

    REQUIRE(results == kSyntaxErrorResult);
  }

  // Can add more
}

TEST_CASE("Test queries that throw SemanticError") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb_read = CreateEmptyPKB();
  std::list<std::string> kSemanticErrorResult = {"SemanticError"};

  // TODO(JL): Add Semantic Error testcases after PR#120 is reviewed
}
