#include <string>
#include <unordered_set>
#include "catch.hpp"

#include "PKB/data/UsesData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test UsesTable") {
    UsesTable uses_table;
    std::unordered_set<std::string> variables{"a"};
    UsesData uses_data(10, variables);
    uses_table.add_row(5, uses_data);

    SECTION("Retrieving UsesTable row") {
        UsesData retrieved_uses_data = uses_table.get_row(5);
        REQUIRE(((retrieved_uses_data.get_line() == 10) &&
                retrieved_uses_data.get_variables().count("a")));
    };
}
