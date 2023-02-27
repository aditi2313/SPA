#include <string>
#include <catch.hpp>

#include "PKB/data/CallsData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test CallsTable") {
    CallsData calls_data1("caller1", "callee11");
    CallsData calls_data2("caller2", "callee21");
    calls_data1.add_to_list("callee12");
    calls_data2.add_to_list("callee22");

    CallsTable calls_table1, calls_table2;
    calls_table1.add_row("caller1", calls_data1);
    calls_table2.add_row("caller2", calls_data2);

    SECTION("Checking if CallsTable rows exists") {
        REQUIRE((calls_table1.exists("caller1") && calls_table2.exists("caller2")));
    };

    SECTION("Checking if CallsTable are empty") {
        REQUIRE((!calls_table1.empty() && !calls_table2.empty()));
    };

    SECTION("Retrieving CallsTable row") {
        CallsData retrieved_calls_data = calls_table1.get_row("caller1");
        REQUIRE(retrieved_calls_data == calls_data1);
    };

    SECTION("Testing CallsTable equality") {
        REQUIRE(!(calls_table1 == calls_table2));
    };
}
