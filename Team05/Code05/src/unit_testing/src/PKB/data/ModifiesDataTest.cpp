#include <string>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ModifiesData int") {
    std::unordered_set<std::string> variables{"a"};
    ModifiesData modifies_data(10, variables);

    SECTION("Retrieving ModifiesData attributes") {
        REQUIRE(modifies_data.get_variables().count("a"));
    }

    SECTION("Retrieving ModifiesData line") {
        REQUIRE((std::holds_alternative<int>(modifies_data.get_index())
                 && std::get<int>(modifies_data.get_index()) == 10));
    }
}

TEST_CASE("Test ModifiesData string") {
    std::unordered_set<std::string> variables{"a"};
    ModifiesData modifies_data("main", variables);

    SECTION("Retrieving ModifiesData attributes") {
        REQUIRE(modifies_data.get_variables().count("a"));
    }

    SECTION("Retrieving ModifiesData line") {
        REQUIRE((std::holds_alternative<std::string>(modifies_data.get_index())
            && std::get<std::string>(modifies_data.get_index()) == "main"));
    }
}
