#include <catch.hpp>
#include "QPS/models/Query.h"
#include "QPS/factories/Export.h"
#include "QPS/models/clauses/Export.h"

using namespace qps; // NOLINT

TEST_CASE("Test Clause static methods") {
  REQUIRE(Clause::is_such_that_rel_name("Modifies") == true);
  REQUIRE(Clause::is_such_that_rel_name("pattern") == false);
}

// TODO(JL): replace with real unit tests after PKB is implemented
TEST_CASE("Test Clause") {
  MasterArgumentFactory master_argument_factory;
  SECTION("Modifies clause should compare equal") {
    QueryPtr query = std::make_unique<Query>();
    auto clause_1 = ModifiesClause(
        master_argument_factory.Create(ArgumentType::kIdentArg, "abc"),
        master_argument_factory.Create(ArgumentType::kIdentArg, "def"));
    auto clause_2 = ModifiesClause(
        master_argument_factory.Create(ArgumentType::kIdentArg, "abc"),
        master_argument_factory.Create(ArgumentType::kIdentArg, "def"));

    REQUIRE(clause_1 == clause_2);
  };

  SECTION("Different clause types with same arguments "
          "should not compare equal") {
    QueryPtr query = std::make_unique<Query>();
    auto modifies_clause = ModifiesClause(
        master_argument_factory.Create(ArgumentType::kIntegerArg, "123"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "456"));

    auto pattern_clause = PatternAssignClause(
        master_argument_factory.Create(ArgumentType::kIntegerArg, "123"),
        master_argument_factory.Create(ArgumentType::kIntegerArg, "456"));

    REQUIRE(modifies_clause != pattern_clause);
  }
}
