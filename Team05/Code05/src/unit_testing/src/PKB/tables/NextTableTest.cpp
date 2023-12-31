#include <string>
#include <catch.hpp>

#include "PKB/data/NextData.h"
#include "PKB/tables/DoubleIndexTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test NextTable") {
    NextData next_data1(1);
    NextData next_data2(11);
    next_data1.add_to_next_im_list(2);
    next_data2.add_to_next_im_list(12);

    NextDTable next_table1, next_table2;
    next_table1.add_row(1, next_data1.get_next_im_list(), next_data1);
    next_table2.add_row(11, next_data2.get_next_im_list(), next_data2);

    SECTION("Checking if NextTable rows exists") {
        REQUIRE((next_table1.exists(1) && next_table2.exists(11)));
    };

    SECTION("Checking if NextTable are empty") {
        REQUIRE((!next_table1.empty() && !next_table2.empty()));
    };

    SECTION("Retrieving NextTable row") {
        NextData retrieved_next_data = next_table1.get_row(1);
        REQUIRE(retrieved_next_data == next_data1);
    };

    SECTION("Testing NextTable equality") {
        REQUIRE(!(next_table1 == next_table2));
    };
}
