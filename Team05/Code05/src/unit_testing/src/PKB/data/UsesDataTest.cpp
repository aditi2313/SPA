#include <string>
#include <vector>
#include <catch.hpp>

#include "PKB/data/UsesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test UsesData") {
    std::unordered_set<std::string> variables = {"a"};
    UsesData uses_data(10, variables);

    SECTION("Retrieving UsesData attributes") {
        REQUIRE(uses_data.get_variables().count("a"));
    };

    SECTION("Retrieving UsesData line") {
        REQUIRE(uses_data.get_line() == 10);
    };
}
