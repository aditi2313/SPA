#include <catch.hpp>
#include <functional>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/SourceProcessor.h"
#include "common/filter/filters/PredicateFilter.h"

using namespace pkb;  // NOLINT
using namespace sp;   // NOLINT

template <typename T>
std::unique_ptr<filter::PredicateFilter<T>> generate_true() {
  return std::make_unique<filter::PredicateFilter<T>>([&](T) { return true; });
}

void test_next(std::vector<std::pair<int, int>> next, std::string program) {
  auto ast = SourceProcessor::ParseProgram(program);
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  SourceProcessor::ExtractRelationships(ast, table);
  PKBRead reader(std::move(table));
  auto res = reader.Next(generate_true<NextData>());
  auto res_table = res->get_result();
  for (auto& [l, n] : next) {
    REQUIRE(res_table->exists(l));
    auto row = res_table->get_row(l);
    auto im_list = row.get_next_im_list();
    REQUIRE(im_list.count(n));
  }
}

TEST_CASE("Test generation of next for program") {
  test_next(
      {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 5}, {5, 7}, {7, 8}, {7, 9}},
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
  test_next({{1, 2}, {2, 1}, {2, 3}, {3, 2}, {4, 5}, {6, 4}, {5, 6}, {7, 8}},
            "procedure proc {"
            "while (x > 1000) {"                    // 1
            "while (x < 1000) {"                    // 2
            "while (k > 21) {"                      // 3
            "while (k < 2) {"                       // 4
            "read x;"                               // 5
            "print x; }}}}}"                        // 6
            "procedure extra { read x; print x; }"  // 7, 8
  );
}
