#include <string>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/data/UsesData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test int line UsesTable") {
    std::unordered_set<std::string> variables1{"a", "b", "c"};
    std::unordered_set<std::string> variables2{"d", "e", "f"};
    UsesData uses_data1(1, variables1);
    UsesData uses_data2(3, variables2);

    UsesTable uses_table1, uses_table2;
    uses_table1.add_row(5, uses_data1);
    uses_table2.add_row(5, uses_data2);

    SECTION("Checking if UsesTable rows exists") {
        REQUIRE((uses_table1.exists(5) && uses_table2.exists(5)));
    };

    SECTION("Checking if UsesTable are empty") {
        REQUIRE((!uses_table1.empty() && !uses_table2.empty()));
    };

    SECTION("Retrieving UsesTable row") {
        UsesData retrieved_uses_data = uses_table1.get_row(5);
        REQUIRE(retrieved_uses_data == uses_data1);
    };

    SECTION("Testing UsesTable equality") {
        REQUIRE(!(uses_table1 == uses_table2));
    };
}

TEST_CASE("Test string line UsesTable") {
    UsesTable uses_table1;
    std::unordered_set<std::string> variables1{"a", "b", "c"};
    UsesData uses_data1("main", variables1);
    uses_table1.add_row("main", uses_data1);

    UsesTable uses_table2;
    std::unordered_set<std::string> variables2{"d", "e", "f"};
    UsesData uses_data2("add", variables2);
    uses_table2.add_row("add", uses_data2);

    SECTION("Checking if UsesTable rows exists") {
        REQUIRE((uses_table1.exists("main") && uses_table2.exists("add")));
    }

    SECTION("Checking if UsesTable are empty") {
        REQUIRE((!uses_table1.empty() && !uses_table2.empty()));
    }

    SECTION("Retrieving UsesTable row") {
        UsesData retrieved_uses_data = uses_table1.get_row("main");
        REQUIRE(retrieved_uses_data == uses_data1);
    }

    SECTION("Testing UsesTable equality") {
        REQUIRE(!(uses_table1 == uses_table2));
    }
}
