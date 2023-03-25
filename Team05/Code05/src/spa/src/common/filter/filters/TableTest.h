#pragma once

#include <exception>
#include <memory>
#include <vector>

namespace filter {

template <class Table>
class TableTest {
 public:
  /// <summary>
  /// Tests the given table.
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  virtual bool TestTable(const Table&) = 0;

  virtual ~TestTable() = default;
};

template <class Table, class Index, class SecondIndex>
class DoubleIndexTest : public TableTest<Table> {
 public:
  bool TestTable(const Table& table) override {
    return table.exists(index_, s_index_);
  }

  DoubleIndexTest() : s_index_(s_index), index_(index) {}

 private:
  Index& index_;
  SecondIndex& s_index_;
};

template <class Table, class Index>
class ReverseIndexTest : public TableTest<Table> {
 public:
  bool FilterTable(const Table& table) override { return table.exists2(index); }
  ReverseIndexFilter(Index index) : index_(index) {}

 private:
  Index index_;
};

template <class Table, class Index>
class IndexTest : public TableTest<Table> {
 public:
  IndexTest(Index index) : index_(index) {}
  bool TestTable(const Table& table) override { return table.exists(index); }
};

}  // namespace filter
