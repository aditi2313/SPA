#include <string>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ModifiesData") {
    std::unordered_set<std::string> variables{"a"};
    ModifiesData modifies_data(10, variables);

    SECTION("Retrieving ModifiesData attributes") {
        REQUIRE(modifies_data.get_variables().count("a"));
    };

    SECTION("Retrieving ModifiesData line") {
        REQUIRE(modifies_data.get_line() == 10);
    };
}
