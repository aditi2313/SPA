#include <memory>
#include <string>
#include <utility>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/Export.h"

#include "models/AST/factor_node/FactorNode.h"

using namespace pkb;  // NOLINT

TEST_CASE("PKB read and write test") {
  // test that read works
  SECTION("PKB read and writes modifies") {
    std::unique_ptr<PKBRelationTable> table =
        std::make_unique<PKBRelationTable>();
    PKBWrite pkb_write(std::move(table));
    std::unordered_set<std::string> variables = {"a", "b", "c"};
    IndexableTable<ModifiesData> expected_table;
    expected_table.add_row(10, ModifiesData(10, variables));

    pkb_write.AddModifiesData(10, variables);
    table = pkb_write.ProcessTableAndEndWrite();

    PKBRead pkb_read(std::move(table));
    //std::unique_ptr<ModifiesTable> result =
    //    pkb_read.Modifies(std::make_unique<filter::ModifiesIndexFilter>(10));
    //REQUIRE(expected_table == *(result));
  }

  SECTION("PKB read and writes assign") {
    std::unique_ptr<PKBRelationTable> table =
        std::make_unique<PKBRelationTable>();
    PKBWrite pkb_write(std::move(table));
    pkb_write.AddAssignData("some", 10, std::make_unique<ast::ConstNode>(5));
    IndexableTable<AssignData> expected_table;
    expected_table.add_row(
        10, AssignData(
            "some", 10, std::make_unique<ast::ConstNode>(5)));
    table = pkb_write.EndWrite();

    PKBRead pkb_read(std::move(table));
    //auto result =
    //    pkb_read.Assigns(std::make_unique<filter::AssignIndexFilter>(10));

    // REQUIRE(expected_table == *(result));
  }
}
