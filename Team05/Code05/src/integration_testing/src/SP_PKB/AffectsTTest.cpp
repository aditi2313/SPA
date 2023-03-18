#include <string>
#include <unordered_map>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/SourceProcessor.h"

using namespace sp;   // NOLINT
using namespace pkb;  // NOLINT

void TestPKBAffectsT(
    std::unordered_map<int, std::unordered_set<int>> expected_table,
    std::string program) {
  auto root = SourceProcessor::ParseProgram(program);
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  SourceProcessor::ExtractRelationships(root, table);
  PKBRead reader(std::move(table));

  for (auto &[line, affected_lines] : expected_table) {
    REQUIRE(reader.AffectsT(line) == affected_lines);
  }
}

TEST_CASE("Simple affectsT testcase") {
  TestPKBAffectsT({
                      {1, {2, 3}},
                      {2, {3}},
                      {3, {}}},
                  "procedure name {"
                  "x = a;"
                  "v = x;"
                  "z = v;"
                  "}");
}

TEST_CASE("Complicated affectsT testcase") {
  TestPKBAffectsT({
                      {1, {4, 8, 10, 11, 12}},
                      {2, {6, 10, 11, 12}},
                      {3, {}},
                      {4, {4, 8, 10, 11, 12}},
                      {5, {}},
                      {6, {6, 10, 11, 12}},
                      {7, {}},
                      {8, {8, 10, 11, 12}},
                      {9, {10, 11, 12}},
                      {10, {10, 11, 12}},
                      {11, {12}},
                      {12, {12}},
                      {13, {14}},
                      {14, {}},
                      {15, {}}},
                  "procedure Second {"
                  "x = 0; "              // 1
                  "i = 5; "              // 2
                  "while (i != 0) {"     // 3
                  "x = x + 2*y; "        // 4
                  "call Third;"          // 5
                  "i = i - 1; }"         // 6
                  "if (x == 1) then {"   // 7
                  "x = x + 1; }"         // 8
                  "else { z = 1; }"      // 9
                  "z = z + x + i; "      // 10
                  "y = z + 2; "          // 11
                  "x = x * y + z; } "    // 12
                  "procedure Third { "
                  "z = 5; "              // 13
                  "v = z; "              // 14
                  "print v; "            // 15
                  "}");
}
