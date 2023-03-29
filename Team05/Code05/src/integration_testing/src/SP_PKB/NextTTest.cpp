#include <catch.hpp>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/Export.h"
#include "common/filter/filters/PredicateFilter.h"

void TestPKBNextT(
    std::unordered_map<int, std::unordered_set<int>> expected_table,
    std::string program) {
  auto root = sp::SourceProcessor::ParseProgram(program);
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));

  for (auto &[line, next_lines] : expected_table) {
    REQUIRE(reader.NextT(line) == next_lines);
  }
}

TEST_CASE("Test SP and PKB integration for NextT data") {
  SECTION("One statement - empty table") {
    TestPKBNextT({}, "procedure next { x = 3; }");
  }

  SECTION("Three statements") {
    std::string program = "procedure next { x = 5; read x; print x; }";

    TestPKBNextT({{1, {2, 3}}, {2, {3}}}, program);
  }

  SECTION("Double nested while loop") {
    std::string program =
        "procedure next { while (x > 5) { read x; while (y < 3) { read y; } } "
        "}";

    TestPKBNextT({{1, {1, 2, 3, 4}},
                  {2, {1, 2, 3, 4}},
                  {3, {1, 2, 3, 4}},
                  {4, {1, 2, 3, 4}}},
                 program);
  }

  SECTION("Calls statement within while") {
    std::string program =
        "procedure next { while (y < 2) { call helper; } } procedure helper { "
        "while (x == 4) { x = 3; } }";

    TestPKBNextT({{1, {1, 2}}, {2, {1, 2}}, {3, {3, 4}}, {4, {3, 4}}},
                 program);
  }
}
