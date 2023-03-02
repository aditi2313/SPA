#include <string>
#include <vector>
#include <catch.hpp>

#include "PKB/data/UsesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test UsesData int") {
    std::unordered_set<std::string> variables = {"a"};
    UsesData uses_data(10, variables);

    SECTION("Retrieving UsesData attributes") {
        REQUIRE(uses_data.get_variables().count("a"));
    };

    SECTION("Retrieving UsesData line") {
        REQUIRE((std::holds_alternative<int>(uses_data.get_index())
                && std::get<int>(uses_data.get_index()) == 10));
    }
}

TEST_CASE("Test UsesData string") {
    std::unordered_set<std::string> variables = {"a"};
    UsesData uses_data("main", variables);

    SECTION("Retrieving UsesData attributes") {
        REQUIRE(uses_data.get_variables().count("a"));
    }

    SECTION("Retrieving UsesData line") {
        REQUIRE((std::holds_alternative<std::string>(uses_data.get_index())
                 && std::get<std::string>(uses_data.get_index()) == "main"));
    }
}
