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
  TestPKBAffects({{1, {1, 2}}},
                 "procedure name {"
                 "x = x + 1;"
                 "print x;"
                 "}");
}
