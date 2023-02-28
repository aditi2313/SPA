#include <string>
#include <catch.hpp>

#include "PKB/data/NextData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test NextData") {
    NextData next_data(1, 2);

    SECTION("Retrieving NextData line") {
        REQUIRE(next_data.get_line() == 1);
    };

    SECTION("Retrieving NextData next line") {
        REQUIRE(next_data.get_next() == 2);
    };

    SECTION("Retrieving NextData next_list") {
        next_data.add_to_list(3);
        std::unordered_set<int> expected_next_list{2, 3};
        REQUIRE(next_data.get_next_list() == expected_next_list);
    };
}
