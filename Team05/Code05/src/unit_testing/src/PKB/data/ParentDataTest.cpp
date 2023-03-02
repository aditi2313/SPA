#include <string>
#include <catch.hpp>

#include "PKB/data/ParentData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ParentData") {
    ParentData parent_data(10);
    parent_data.add_direct_child(11);
    parent_data.add_to_all_children(13);

    std::unordered_set<int> expected_direct_children{11};
    std::unordered_set<int> expected_total_children{13};

    SECTION("Retrieving ParentData direct children") {
        REQUIRE(parent_data.get_direct_children() == expected_direct_children);
    };

    SECTION("Retrieving ParentData all children") {
        REQUIRE(parent_data.get_all_children() == expected_total_children);
    };

    SECTION("Retrieving ParentData line") {
        REQUIRE(parent_data.get_index() == 10);
    };
}
