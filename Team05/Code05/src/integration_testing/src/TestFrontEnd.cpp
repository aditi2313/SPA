#include "models/AST/TNode.h"
#include <catch.hpp>

void require(bool b) {
  REQUIRE(b);
}

TEST_CASE("1st Test") {

  require(1 == 1);
}
