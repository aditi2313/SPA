#include <catch.hpp>

#include "models/AST/TNode.h"

void require(bool b) { REQUIRE(b); }

TEST_CASE("1st Test") { require(1 == 1); }
