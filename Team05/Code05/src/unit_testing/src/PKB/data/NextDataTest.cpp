#include <string>
#include <catch.hpp>

#include "PKB/data/NextData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test NextData") {
    NextData next_data(1);
    next_data.add_to_next_im_list(2);

    SECTION("Retrieving NextData line") {
        REQUIRE(next_data.get_index() == 1);
    };

    SECTION("Retrieving NextData next_im_list line") {
        std::unordered_set<int> expected = {2};
        REQUIRE(next_data.get_next_im_list() == expected);
    };
}
