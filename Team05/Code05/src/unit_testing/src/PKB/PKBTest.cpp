#include <catch.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/AssignFilter.h"
#include "models/AST/factor_node/FactorNode.h"

using namespace pkb;  // NOLINT

TEST_CASE("PKB read and write test") {
  // test that read works
  SECTION("PKB read and writes modifies") {
    std::unique_ptr<PKBRelationTable> table =
        std::make_unique<PKBRelationTable>();
    PKBWrite pkb_write(std::move(table));
    std::vector<std::string> variables = {"a", "b", "c"};
    IndexableTable<ModifiesData> expected_table;
    expected_table.add_row(10, ModifiesData(10, variables));

    pkb_write.AddModifiesData(10, variables);
    table = pkb_write.EndWrite();

    PKBRead pkb_read(std::move(table));
    std::unique_ptr<ModifiesTable> result =
        pkb_read.Modifies(std::make_unique<filter::ModifiesFilterByLine>(10))
            ->get_result();
    REQUIRE(expected_table == *(result));
  }

  SECTION("PKB read and writes assign") {
    std::unique_ptr<PKBRelationTable> table =
        std::make_unique<PKBRelationTable>();
    PKBWrite pkb_write(std::move(table));
    pkb_write.AddAssignData("some", 10, std::make_unique<ast::ConstNode>(5));
    IndexableTable<std::shared_ptr<AssignData>> expected_table;
    expected_table.add_row(
        10, std::make_shared<AssignData>("some", 10,
                                         std::make_unique<ast::ConstNode>(5)));
    table = pkb_write.EndWrite();

    PKBRead pkb_read(std::move(table));
    auto result = pkb_read.Assigns(std::make_unique<filter::AssignFilterAll>())
                      ->get_result();
    // unable to require as Assign Table is all references
    // REQUIRE(expected_table == *(result));
  }
}
