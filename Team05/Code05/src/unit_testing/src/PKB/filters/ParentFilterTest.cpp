#include <unordered_set>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/Export.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test processing of multiple parents line") {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite writer(std::move(table));
  writer.AddParentData(2, 3);
  writer.AddParentData(3, 4);
  writer.AddParentData(4, 5);
  writer.AddParentData(5, 6);
  writer.AddParentData(7, 8);
  for (int i = 2; i <= 8; ++i) writer.add_stmt(i);
  table = writer.ProcessTableAndEndWrite();
  
  PKBRead reader(std::move(table));

  SECTION("Test slightly long list") {
    std::unordered_set<int> expected{3, 4, 5, 6};
    filter::ParentIndexFilter ftr(2);
    auto& result = reader.Parent(ftr);
    REQUIRE(result.read_data().get_all_children() == expected);
  }
  SECTION("Test slightly short list") {
    std::unordered_set<int> expected{5, 6};
    filter::ParentIndexFilter ftr(4);
    auto& result = reader.Parent(ftr);
    REQUIRE(result.read_data().get_all_children() == expected);
  }
}
