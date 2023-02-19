#include <string>
#include <catch.hpp>

#include "PKB/data/ParentData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ParentData") {
    ParentData parent_data(10, 11);
    std::unordered_set<int> children_list = {11, 12};

    SECTION("Retrieving ParentData parent line") {
        REQUIRE(parent_data.get_child() == 11);
    };

    SECTION("Retrieving ParentData line") {
        REQUIRE(parent_data.get_line() == 10);
    };

    SECTION("Adding and Retrieving ParentData list") {
        parent_data.add_children(12);
        REQUIRE(parent_data.get_children_set() == children_list);
    };
}
