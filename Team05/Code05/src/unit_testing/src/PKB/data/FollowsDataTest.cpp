#include <string>
#include <catch.hpp>

#include "PKB/data/FollowsData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test FollowsData") {
    FollowsData follows_data(11, 10);
    std::unordered_set<int> follows_list_test = {9, 10};

    SECTION("Retrieving FollowsData parent line") {
        REQUIRE(follows_data.get_follows() == 10);
    };

    SECTION("Retrieving FollowsData line") {
        REQUIRE(follows_data.get_line() == 11);
    };

    SECTION("Adding and Retrieving FollowsData list") {
        follows_data.add_to_list(9);
        REQUIRE(follows_data.get_follows_list() == follows_list_test);
    };
}
