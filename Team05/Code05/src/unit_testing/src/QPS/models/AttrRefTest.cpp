#include <catch.hpp>
#include "QPS/models/AttrRef.h"

using qps::AttrRef; // NOLINT

TEST_CASE("Test AttrRef") {
  REQUIRE(AttrRef::is_attr_ref("") == false);
  REQUIRE(AttrRef::is_attr_ref("var.varName") == true);
  REQUIRE(AttrRef::is_attr_ref("p.procName") == true);
  REQUIRE(AttrRef::is_attr_ref("constant.value") == true);
  REQUIRE(AttrRef::is_attr_ref("stmt.stmt#") == true);

  REQUIRE(AttrRef::is_attr_ref("varvarName") == false);
  REQUIRE(AttrRef::is_attr_ref("var.var") == false);
  REQUIRE(AttrRef::is_attr_ref("p.Name") == false);
  REQUIRE(AttrRef::is_attr_ref("constant.VALUE") == false);
  REQUIRE(AttrRef::is_attr_ref("stmt.stmtNum") == false);
}