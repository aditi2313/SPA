#include <string>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test ModifiesTable") {
    std::unordered_set<std::string> variables1{"a", "b", "c"};
    std::unordered_set<std::string> variables2{"d", "e", "f"};
    ModifiesData modifies_data1(1, variables1);
    ModifiesData modifies_data2(3, variables2);

    ModifiesTable modifies_table1;
    modifies_table1.add_row(5, modifies_data1);
    ModifiesTable modifies_table2;
    modifies_table2.add_row(5, modifies_data2);

    SECTION("Checking if ModifiesTable rows exists") {
        REQUIRE((modifies_table1.exists(5) && modifies_table2.exists(5)));
    };

    SECTION("Checking if ModifiesTable row is empty") {
        REQUIRE(!(modifies_table1.empty() && modifies_table2.empty()));
    };

    SECTION("Retrieving ModifiesTable row") {
        ModifiesData retrieved_modifies_data = modifies_table1.get_row(5);
        REQUIRE(retrieved_modifies_data == modifies_data1);
    };

    SECTION("Testing ModifiesTable equality") {
        REQUIRE(!(modifies_table1 == modifies_table2));
    };
}
