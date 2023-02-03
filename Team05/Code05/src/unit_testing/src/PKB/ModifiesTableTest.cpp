#include <string>
#include <vector>
#include <catch.hpp>

#include "PKB/ModifiesTable.h"
#include "PKB/ModifiesData.h"

using namespace pkb; // NOLINT

TEST_CASE("Test ModifiesTable") {
    ModifiesTable modifies_table;
    ModifiesData modifies_data;
    std::vector<std::string> variables{"a"};
    modifies_data.line_ = 10;
    modifies_data.variables_ = variables;
    modifies_table.add_row(modifies_data);

    SECTION("Retrieving ModifiesTable row") {
        ModifiesData retrieved_modifies_data = modifies_table.get_row(0);
        REQUIRE(((retrieved_modifies_data.line_ == 10)
                 && (retrieved_modifies_data.variables_.at(0) == "a")));
    };
}
