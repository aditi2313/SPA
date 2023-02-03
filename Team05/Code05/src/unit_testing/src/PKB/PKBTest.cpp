#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/ModifiesFilter.h"

using namespace pkb;  // NO LINT

TEST_CASE("PKB read and write test") {
  // test that read works
  SECTION("PKB read and writes modifies") {
    std::unique_ptr<PKBRelationTable> table =
        std::make_unique<PKBRelationTable>();
    PKBWrite pkb_write(std::move(table));
    std::vector<std::string> variables = {"a", "b", "c"};
    IndexableTable<ModifiesData> expected_table;
    expected_table.add_row(10, ModifiesData(10, variables));

    pkb_write.AddModifies(10, variables);
    table = pkb_write.EndWrite();
    PKBRead pkb_read(std::move(table));
    REQUIRE(expected_table == *(pkb_read.Modifies(std::make_unique<filter::ModifiesFilterByLine>(10))));
  }
}
