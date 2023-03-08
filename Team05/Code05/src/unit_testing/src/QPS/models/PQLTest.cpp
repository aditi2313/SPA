#include <catch.hpp>
#include "QPS/models/PQL.h"

using qps::PQL; // NOLINT

TEST_CASE("Test PQL") {
  SECTION("Validation methods") {
    REQUIRE(PQL::is_ident("a") == true);
    REQUIRE(PQL::is_ident("abc") == true);
    REQUIRE(PQL::is_ident("abc0123") == true);
    REQUIRE(PQL::is_ident("1") == false);
    REQUIRE(PQL::is_ident("a&") == false);

    REQUIRE(PQL::is_integer("10") == true);
    REQUIRE(PQL::is_integer("1234567890") == true);
    REQUIRE(PQL::is_integer("0") == false);
    REQUIRE(PQL::is_integer("01") == false);

    REQUIRE(PQL::is_pattern_wildcard("_\"x\"_") == true);
    REQUIRE(PQL::is_pattern_wildcard("\"x\"_") == false);
    REQUIRE(PQL::is_pattern_wildcard("_\"x\"") == false);

    REQUIRE(PQL::is_such_that_rel_name("Modifies") == true);

    REQUIRE(PQL::is_attr_ref("") == false);
    REQUIRE(PQL::is_attr_ref("var.varName") == true);
    REQUIRE(PQL::is_attr_ref("p.procName") == true);
    REQUIRE(PQL::is_attr_ref("constant.value") == true);
    REQUIRE(PQL::is_attr_ref("stmt.stmt#") == true);


    REQUIRE(PQL::is_attr_ref("varvarName") == false);
    REQUIRE(PQL::is_attr_ref("var.var") == false);
    REQUIRE(PQL::is_attr_ref("p.Name") == false);
    REQUIRE(PQL::is_attr_ref("constant.VALUE") == false);
    REQUIRE(PQL::is_attr_ref("stmt.stmtNum") == false);
  };
}

