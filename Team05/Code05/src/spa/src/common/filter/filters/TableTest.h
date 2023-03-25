#pragma once

#include <exception>
#include <memory>
#include <vector>

namespace filter {

// TODO(Gab) remove if no time
// temporary code related to trying to make
// use of a boolean return value in pkb for optimisations
template <class Table>
class TableTest {
 public:
  /// <summary>
  /// Tests the given table.
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  virtual bool TestTable(const Table&) = 0;

  virtual ~TableTest() = default;
};

template <class Table, class Index, class SecondIndex>
class DoubleIndexTest : public TableTest<Table> {
 public:
  bool TestTable(const Table& table) override {
    return table.exists(index_, s_index_);
  }

  ~DoubleIndexTest() {}

  explicit DoubleIndexTest(Index index, SecondIndex s_index)
      : s_index_(s_index), index_(index) {}

 private:
  Index& index_;
  SecondIndex& s_index_;
};

template <class Table, class Index>
class ReverseIndexTest : public TableTest<Table> {
 public:
  bool FilterTable(const Table& table) override { return table.exists2(index); }
  explicit ReverseIndexTest(Index index) : index_(index) {}
  ~ReverseIndexTest() {}

 private:
  Index index_;
};

template <class Table, class Index>
class IndexTest : public TableTest<Table> {
 public:
  explicit IndexTest(Index index) : index_(index) {}
  ~IndexTest() {}
  bool TestTable(const Table& table) override { return table.exists(index); }

 private:
  Index index_;
};

}  // namespace filter
