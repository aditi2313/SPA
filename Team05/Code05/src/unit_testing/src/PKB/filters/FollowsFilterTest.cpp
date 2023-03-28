#include <unordered_set>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/IndexFilter.h"
#include "common/filter/filters/double_index/Export.h"

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
  table = writer.ProcessTableAndEndWrite();
  PKBRead reader(std::move(table));
  SECTION("Test slightly long list") {
    std::unordered_set<int> expected{3, 4, 5, 6};
    filter::FollowsDIndexFilter filter(2);
    auto& result = reader.Follows(filter);
    REQUIRE(result.read_data().get_follows_list() == expected);
  }
  SECTION("Test slightly short list") {
    std::unordered_set<int> expected{5, 6};
    filter::FollowsDIndexFilter filter(4);
    auto& result = reader.Follows(filter);
    while (!result.reached_end()) {
      if (result.read_data().get_index() == 4) break;

    }
    REQUIRE(result.read_data().get_follows_list() == expected);
  }
}
