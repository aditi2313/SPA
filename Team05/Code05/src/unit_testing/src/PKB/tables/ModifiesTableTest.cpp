#include <string>
#include <unordered_set>
#include "catch.hpp"

#include "PKB/data/ModifiesData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test ModifiesTable") {
  ModifiesTable modifies_table;
  std::unordered_set<std::string> variables{"a"};
  ModifiesData modifies_data(10, variables);
  modifies_table.add_row(5, modifies_data);

  SECTION("Retrieving ModifiesTable row") {
    ModifiesData retrieved_modifies_data = modifies_table.get_row(5);
    REQUIRE(((retrieved_modifies_data.get_line() == 10) &&
        retrieved_modifies_data.get_variables().count("a")));
  };
}
