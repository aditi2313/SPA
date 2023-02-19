#include <string>
#include <catch.hpp>

#include "PKB/data/FollowsData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test FollowsTable") {
    FollowsData follows_data1(11, 10);
    FollowsData follows_data2(3, 2);
    follows_data1.add_to_list(9);
    follows_data2.add_to_list(1);

    FollowsTable follows_table1;
    follows_table1.add_row(5, follows_data1);
    FollowsTable follows_table2;
    follows_table2.add_row(5, follows_data2);

    SECTION("Checking if FollowsTable rows exists") {
        REQUIRE((follows_table1.exists(5) && follows_table2.exists(5)));
    };

    SECTION("Checking if FollowsTable row is empty") {
        REQUIRE(!(follows_table1.empty() && follows_table2.empty()));
    };

    SECTION("Retrieving FollowsTable row") {
        FollowsData retrieved_follows_data = follows_table1.get_row(5);
        REQUIRE(retrieved_follows_data == follows_data1);
    };

    SECTION("Testing FollowsTable equality") {
        REQUIRE(!(follows_table1 == follows_table2));
    };
}
