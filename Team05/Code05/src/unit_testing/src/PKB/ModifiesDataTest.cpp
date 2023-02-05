#include <string>
#include <vector>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ModifiesData") {
    std::vector<std::string> variables{"a"};
    ModifiesData modifies_data(10, variables);

    SECTION("Retrieving ModifiesData attributes") {
        REQUIRE(((modifies_data.get_line() == 10)
            && (modifies_data.get_variables().at(0) == "a")));
    };
}