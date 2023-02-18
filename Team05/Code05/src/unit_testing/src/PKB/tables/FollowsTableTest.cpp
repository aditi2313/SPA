#include <string>
#include <catch.hpp>

#include "PKB/data/FollowsData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test FollowsTable") {
    FollowsTable follows_table;
    FollowsData follows_data(11, 10);
    follows_table.add_row(5, follows_data);

    SECTION("Retrieving FollowsTable row") {
        FollowsData retrieved_follows_data = follows_table.get_row(5);
        REQUIRE(((retrieved_follows_data.get_line() == 11) &&
                retrieved_follows_data.get_follows() == 10));
    };
}
