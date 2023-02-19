#include <string>
#include <catch.hpp>

#include "PKB/data/ParentData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test ParentTable") {
    ParentData parent_data1(11, 10);
    ParentData parent_data2(3, 2);
    parent_data1.add_parent(9);
    parent_data2.add_parent(1);

    ParentTable parent_table1;
    parent_table1.add_row(5, parent_data1);
    ParentTable parent_table2;
    parent_table2.add_row(5, parent_data2);

    SECTION("Checking if ParentTable rows exists") {
        REQUIRE((parent_table1.exists(5) && parent_table2.exists(5)));
    };

    SECTION("Checking if ParentTable row is empty") {
        REQUIRE(!(parent_table1.empty() && parent_table2.empty()));
    };

    SECTION("Retrieving ParentTable row") {
        ParentData retrieved_parent_data = parent_table1.get_row(5);
        REQUIRE(retrieved_parent_data == parent_data1);
    };

    SECTION("Testing ParentTable equality") {
        REQUIRE(!(parent_table1 == parent_table2));
    };
}
