#include <memory>
#include <string>
#include <vector>
#include <list>
#include <catch.hpp>

#include "SP/parser/expression/ExpressionParser.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "PKB/PKBRead.h"
#include "QPS/QPS.h"

using namespace pkb;  // NOLINT
using namespace qps;  // NOLINT

using assign_data = std::tuple<std::string, int, std::string>;

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKB(
    std::vector<assign_data> data
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  for (auto [var, line, expr] : data) {
    sp::ExpressionParser expr_parser;
    sp::Lexer lxr(expr);
    auto ASTNode = expr_parser.parse(lxr);
    pkb_write.AddAssignData(var, line, std::move(ASTNode));
    pkb_write.AddModifiesData(line, {var});
    pkb_write.add_assign(line);
    pkb_write.add_stmt(line);
  }

  return std::make_unique<PKBRead>(pkb_write.ProcessTableAndEndWrite());
}

TEST_CASE("Test PKB and QPS integration for Pattern clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKB(
      {
          {"abc", 1, "x + y"},
          {"v", 2, "abra + cadabra"},
          {"v", 3, "1 + 2 + 3"},
          {"abc", 4, "x + 1 + 3"},
      });

  SECTION("pattern a(_, _) should return correct results") {
    std::string query_string = "assign a; Select a pattern a(_, _)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"1", "2", "3", "4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, \"x + y\") should return correct results") {
    std::string query_string = "assign a; Select a pattern a(_, \"x + y\")";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"1"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, \"abra + cadabra\") should return correct results") {
    std::string query_string = "assign a; Select a "
                               "pattern a(_, _\"abra+cadabra\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"2"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, _\"x\"_) should return correct results") {
    std::string query_string = "assign a; Select a pattern a(_, _\"x\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"1", "4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, _\"cadabra\"_) should return correct results") {
    std::string query_string = "assign b; Select b "
                               "pattern b(_, _\"cadabra\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"2"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, _\"2\"_) should return correct results") {
    std::string query_string = "assign c; Select c "
                               "pattern c(_, _\"2\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, _\"1 + 2\"_) should return correct results") {
    std::string query_string = "assign c; Select c "
                               "pattern c(_, _\"1 + 2\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, _\"2 + 3\"_) should return correct results") {
    std::string query_string = "assign c; Select c "
                               "pattern c(_, _\"2 + 3\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{};  // Shouldn't match with 3
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(_, _\"x + 1\"_) should return correct results") {
    std::string query_string = "assign c; Select c "
                               "pattern c(_, _\"x + 1\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(ident, _) should return correct results") {
    std::string query_string = "assign a; Select a pattern a(\"v\", _)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"2", "3"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(syn, _) should return correct results") {
    std::string query_string = "assign a; variable var; "
                               "Select a pattern a(var, _)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"1", "2", "3", "4"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(syn, _) should return correct results") {
    std::string query_string = "assign a; variable var; "
                               "Select var pattern a(var, _\"x\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"abc"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }

  SECTION("pattern a(syn, _) with multiple select "
          "should return correct results") {
    std::string query_string = "assign a; variable var; "
                               "Select <a, var> pattern a(var, _\"x\"_)";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"1, abc", "4, abc"};
    REQUIRE(util::CompareResults(actual_results, expected_results));
  }
}
