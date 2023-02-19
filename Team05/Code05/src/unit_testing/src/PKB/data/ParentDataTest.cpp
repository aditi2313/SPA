#include <string>
#include <catch.hpp>

#include "PKB/data/ParentData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ParentData") {
    ParentData parent_data(11, 10);
    std::unordered_set<int> parent_list_test = {9, 10};

    SECTION("Retrieving ParentData parent line") {
        REQUIRE(parent_data.get_parent() == 10);
    };

    SECTION("Retrieving ParentData line") {
        REQUIRE(parent_data.get_line() == 11);
    };

    SECTION("Adding and Retrieving ParentData list") {
        parent_data.add_parent(9);
        REQUIRE(parent_data.get_parent_set() == parent_list_test);
    };
}
