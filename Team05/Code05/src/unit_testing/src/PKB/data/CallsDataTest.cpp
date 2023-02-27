#include <string>
#include <catch.hpp>

#include "PKB/data/CallsData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test CallsData") {
    CallsData calls_data("caller", "callee1");

    SECTION("Retrieving CallsData caller") {
        REQUIRE(calls_data.get_caller() == "caller");
    };

    SECTION("Retrieving CallsData callee") {
        REQUIRE(calls_data.get_callee() == "callee1");
    };

    SECTION("Retrieving CallsData callee_list") {
        calls_data.add_to_list("callee2");
        std::unordered_set<std::string>
            expected_callee_list{"callee1", "callee2"};
        REQUIRE(calls_data.get_callee_list() == expected_callee_list);
    };
}
