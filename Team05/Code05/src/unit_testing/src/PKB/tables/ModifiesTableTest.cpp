#include <string>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/data/ModifiesData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test int line ModifiesTable") {
    std::unordered_set<std::string> variables1{"a", "b", "c"};
    std::unordered_set<std::string> variables2{"d", "e", "f"};
    ModifiesData modifies_data1(1, variables1);
    ModifiesData modifies_data2(3, variables2);

    ModifiesTable modifies_table1, modifies_table2;
    modifies_table1.add_row(5, modifies_data1);
    modifies_table2.add_row(5, modifies_data2);

    SECTION("Checking if ModifiesTable rows exists") {
        REQUIRE((modifies_table1.exists(5) && modifies_table2.exists(5)));
    };

    SECTION("Checking if ModifiesTable are empty") {
        REQUIRE((!modifies_table1.empty() && !modifies_table2.empty()));
    };

    SECTION("Retrieving ModifiesTable row") {
        ModifiesData retrieved_modifies_data = modifies_table1.get_row(5);
        REQUIRE(retrieved_modifies_data == modifies_data1);
    };

    SECTION("Testing ModifiesTable equality") {
        REQUIRE(!(modifies_table1 == modifies_table2));
    };
}

TEST_CASE("Test string line ModifiesTable") {
    ModifiesTable modifies_table1;
    std::unordered_set<std::string> variables1{"a", "b", "c"};
    ModifiesData modifies_data1("main", variables1);
    modifies_table1.add_row("main", modifies_data1);

    ModifiesTable modifies_table2;
    std::unordered_set<std::string> variables2{"d", "e", "f"};
    ModifiesData modifies_data2("helper", variables2);
    modifies_table2.add_row("helper", modifies_data2);

    SECTION("Checking if ModifiesTable rows exists") {
        REQUIRE((modifies_table1.exists("main")
                 && modifies_table2.exists("helper")));
    };

    SECTION("Checking if ModifiesTable are empty") {
        REQUIRE((!modifies_table1.empty() && !modifies_table2.empty()));
    };

    SECTION("Retrieving ModifiesTable row") {
        ModifiesData retrieved_modifies_data = modifies_table1.get_row("main");
        REQUIRE(retrieved_modifies_data == modifies_data1);
    };

    SECTION("Testing ModifiesTable equality") {
        REQUIRE(!(modifies_table1 == modifies_table2));
    };
}
