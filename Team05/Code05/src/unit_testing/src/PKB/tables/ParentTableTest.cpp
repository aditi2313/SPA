#include <string>
#include <catch.hpp>

#include "PKB/data/ParentData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test ParentTable") {
    ParentTable parent_table;
    ParentData parent_data(11, 10);
    parent_table.add_row(5, parent_data);

    SECTION("Retrieving ParentTable row") {
        ParentData retrieved_parent_data = parent_table.get_row(5);
        REQUIRE(((retrieved_parent_data.get_line() == 11) &&
                retrieved_parent_data.get_parent() == 10));
    };
}
