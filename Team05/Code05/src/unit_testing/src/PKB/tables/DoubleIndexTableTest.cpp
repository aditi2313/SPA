#include <string>
#include <unordered_map>
#include <unordered_set>
#include <catch.hpp>

#include "PKB/tables/DoubleIndexTable.h"

using namespace pkb;  // NOLINT

typedef DoubleIndexTable<std::string, int, int> TestedTable;

// TODO(Gab) Move to shared header file
template <class Container, class Data>
void CompareContents(Container c1, Container c2) {
  std::unordered_set<Data> data1;
  std::unordered_set<Data> data2;
  for (auto& data : c1) {
    data1.insert(data);
  }
  for (auto& data : c2) {
    data2.insert(data);
  }
  REQUIRE(data1 == data2);
}

void VerifyMultipleKeys(
    std::unordered_map<int, std::pair<std::string, std::unordered_set<int>>>
        data,
    TestedTable& test_table) {
  for (auto& [p1, second_indexes] : data) {
    test_table.add_row(p1, second_indexes.second, second_indexes.first);
  }
  for (auto& [p1, second_indexes] : data) {
    REQUIRE(test_table.get_row(p1) == second_indexes.first);
  }
}

void VerifySingleKeys(
    std::unordered_map<int, std::pair<std::string, std::unordered_set<int>>>
        data,
    TestedTable& test_table) {
  for (auto& [p1, second_indexes] : data) {
    test_table.add_row(p1, second_indexes.second, second_indexes.first);
  }
  for (auto& [p1, second_indexes] : data) {
    REQUIRE(test_table.get_row(p1) == second_indexes.first);
  }
}
