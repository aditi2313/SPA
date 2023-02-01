#include "SP/models/TNode.h"
#include <catch.hpp>

void require(bool b) {
  REQUIRE(b);
}

TEST_CASE("1st Test") {
  ast::TNode T;
  require(1 == 1);
}
