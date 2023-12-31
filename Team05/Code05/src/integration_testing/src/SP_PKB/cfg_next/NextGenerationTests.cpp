#include <functional>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/SourceProcessor.h"
#include "common/filter/filters/Export.h"

using namespace pkb;  // NOLINT
using namespace sp;   // NOLINT

void TestNext(std::unordered_map<int, std::unordered_set<int>> next,
              std::string program) {
  auto ast = SourceProcessor::ParseProgram(program);
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  SourceProcessor::ExtractRelationships(ast, table);
  PKBRead reader(std::move(table));
  filter::NextPredicateFilter filter([&](NextData) { return true; });

  auto& results_table = reader.Next(filter);
  std::unordered_map<int, std::unordered_set<int>> vals;
  while (!results_table.reached_end()) {
    auto data = results_table.read_data();
    for (auto v : data.get_next_im_list()) {
      vals[data.get_index()].insert(v);
    }
    results_table.increment();
  }
  REQUIRE(next == vals);
}

TEST_CASE("Test generation of next for program") {
  TestNext({{1, {2}},
            {2, {3}},
            {3, {4}},
            {4, {5}},
            {5, {6, 7}},
            {6, {5}},
            {7, {8, 9}}},
           "procedure proc { "
           "val = x;"             // 1
           "x = 2;"               // 2
           "read x;"              // 3
           "print x;"             // 4
           "while (x > 100) {"    // 5
           " read x; }"           // 6
           "if (x > 100) then {"  // 7
           "read x; } else {"     // 8
           "print x; }"           // 9
           "}");
}

TEST_CASE("Deep while nest") {
  TestNext({{1, {2}},
            {2, {1, 3}},
            {3, {2, 4}},
            {4, {5, 3}},
            {6, {4}},
            {5, {6}},
            {7, {8}}},
           "procedure proc {"
           "while (x > 1000) {"                      // 1
           "while (x < 1000) {"                      // 2
           "while (k > 21) {"                        // 3
           "while (k < 2) {"                         // 4
           "read x;"                                 // 5
           "print x; }}}}}"                          // 6
           "procedure extra { read x; print x; }");  // 7, 8
}
