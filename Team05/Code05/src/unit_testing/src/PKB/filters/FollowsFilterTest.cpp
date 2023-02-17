#include <unordered_set>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/IndexFilter.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test processing of multiple follows line") {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite writer(std::move(table));
  writer.AddFollowsData(2, 3);
  writer.AddFollowsData(3, 4);
  writer.AddFollowsData(4, 5);
  writer.AddFollowsData(5, 6);
  writer.AddFollowsData(7, 8);
  table = writer.EndWrite();
  PKBRead reader(std::move(table));
  SECTION("Test slightly long list") {
    std::unordered_set<int> expected{3, 4, 5, 6};
    auto ftr = std::make_unique<filter::IndexFilter<FollowsData>>(2);
    auto result = reader.Follows(std::move(ftr));
    REQUIRE(result->get_result()->get_row(2).get_follows_list() == expected);
  }
  SECTION("Test slightly short list") {
    std::unordered_set<int> expected{5, 6};
    auto ftr = std::make_unique<filter::IndexFilter<FollowsData>>(4);
    auto result = reader.Follows(std::move(ftr));
    REQUIRE(result->get_result()->get_row(4).get_follows_list() == expected);
  }
}
