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
  }

  return std::make_unique<PKBRead>(pkb_write.EndWrite());
}

TEST_CASE("Test PKB and QPS integration for Pattern clause") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKB(
      {
          {"v", 1, "x + y"},
          {"v", 2, "abra + cadabra"}
      });

  SECTION("pattern a(_, \"x+y\") should return correct results") {
    std::string query_string = "assign a; Select a pattern a(_, \"x + y\")";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"1"};
    REQUIRE(actual_results == expected_results);
  }

  SECTION("pattern a(_, \"abra + cadabra\") should return correct results") {
    std::string query_string = "assign a; Select a "
                               "pattern a(_, \"abra + cadabra\")";
    std::list<std::string> actual_results;
    qps.evaluate(query_string, actual_results, pkb);

    std::list<std::string> expected_results{"2"};
    REQUIRE(actual_results == expected_results);
  }
}
