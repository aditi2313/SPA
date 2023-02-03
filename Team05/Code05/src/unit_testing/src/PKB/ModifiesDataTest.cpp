#include <catch.hpp>
#include <string>
#include <vector>
#include "PKB/ModifiesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ModifiesData") {
    ModifiesData modifies_data;
    std::vector<std::string> variables{"a"};
    modifies_data.line_ = 10;
    modifies_data.variables_ = std::vector<std::string> {"a"};

    SECTION("Retrieving ModifiesData attributes") {
        REQUIRE(((modifies_data.line_ == 10)
            && (modifies_data.variables_.at(0) == "a")));
    };
}
