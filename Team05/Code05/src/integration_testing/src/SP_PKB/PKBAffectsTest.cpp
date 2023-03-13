#include <catch.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/SourceProcessor.h"

using namespace sp;   // NOLINT
using namespace pkb;  // NOLINT

void TestPKBAffects(
    std::unordered_map<int, std::unordered_set<int>> expected_table,
    std::string program) {
  auto root = SourceProcessor::ParseProgram(program);
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  SourceProcessor::ExtractRelationships(root, table);
  PKBRead reader(std::move(table));

  for (auto& [line, affected_lines] : expected_table) {
    REQUIRE(reader.Affects(line) == affected_lines);
  }
}

TEST_CASE("Simple affects testcase") {
  TestPKBAffects({{1, {1, 3}}},
                 "procedure name {"
                 "x = x + 1;"
                 "print x;"
                 "y = y + x;"
                 "}");
}

TEST_CASE("Complicated affects testcase") {
  TestPKBAffects({{2, {2, 3}}, {3, {}}},
                 "procedure name {"
                 "while (x < 2)"
                 "{"
                 "x = x + 1;"
                 "}"
                 "y = x + 1;"
                 "}");

  TestPKBAffects(
      {{2, {2, 3}}, {3, {3, 5}}, {5, {5, 2, 6}}, {4, {4, 6}}, {6, {6}}},
      "procedure name {"
      "while (x < 2)"  // 1
      "{"
      "x = x + 2;"  // 2
      "x = x + 1;"  // 3
      "y = y;"      // 4
      "x = x + 3;"  // 5
      "}"
      "y = x + 1 + y;"  // 6
      "}");
}

TEST_CASE("Complicated affects test case in if and while loop") {
  TestPKBAffects({{1, {4}}, {2, {}}, {5, {7, 8}}},
                 "procedure name"
                 "{"
                 "x = 2;"           // 1
                 "y = 3;"           // 2
                 "call procedure;"  // 3
                 "k = x * y;"       // 4
                 "}"
                 "procedure procedure {"
                 "z = 5;"             // 5
                 "if (z > 0) then {"  // 6
                 "y = x + 1;"         // 7
                 "} else {"
                 "y = z + x;"  // 8
                 "}"
                 "}");
}
