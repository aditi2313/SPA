#pragma once
#include <catch.hpp>
#include <vector>

#include "PKB/tables/reader/TableReader.h"

using namespace pkb;  // NOLINT

template <class Data>
bool CheckReaderEquality(std::vector<Data> datas, TableReader<Data>& reader) {
  while (!reader.reached_end()) {
    auto& data = reader.read_data();
    bool accept = false;
    for (auto& d : datas) {
      if (d == data) {
        accept = true;
        break;
      }
    }
    if (!accept) return false;
    reader.increment();
  }
  return true;
}
