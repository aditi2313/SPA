#include <string>
#include <catch.hpp>

#include "PKB/data/CallsData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test CallsData") {
    CallsData calls_data("caller");
    calls_data.add_to_direct_calls("callee1");
    calls_data.add_to_total_calls("callee2");

    SECTION("Retrieving CallsData caller") {
        REQUIRE(calls_data.get_line() == "caller");
    };

    SECTION("Retrieving CallsData direct callees") {
        std::unordered_set<std::string> expected = {"callee1"};
        REQUIRE(calls_data.get_direct_calls() == expected);
    };

    SECTION("Retrieving CallsData total callees") {
        std::unordered_set<std::string> expected = {"callee2"};
        REQUIRE(calls_data.get_total_calls() == expected);
    };
}
