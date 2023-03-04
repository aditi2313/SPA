#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"  // NOLINT
#include "SP/utils/TopologicalSorter.h"

TEST_CASE("Test 1") {
  std::unordered_map<std::string, std::unordered_set<std::string>> called_by = {
      {"A", {"B"}},
      {"B", {"C"}},
      {"C", {"D"}},
      {"D", {"E"}},
      {"E", {}}
  };
  std::vector<std::string> expected_result = {"A", "B", "C", "D", "E"};

  auto actual_result = sp::TopologicalSorter::Sort(called_by);

  REQUIRE(expected_result == actual_result);
}

TEST_CASE("Test 2") {
  std::unordered_map<std::string, std::unordered_set<std::string>> called_by = {
      {"A", {"B", "C", "D"}},
      {"B", {"C", "D"}},
      {"C", {}},
      {"D", {"C"}},
  };
  std::vector<std::string> expected_result = {"A", "B", "D", "C"};

  auto actual_result = sp::TopologicalSorter::Sort(called_by);

  REQUIRE(expected_result == actual_result);
}
