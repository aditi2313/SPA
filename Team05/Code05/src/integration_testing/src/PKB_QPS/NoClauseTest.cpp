#include <memory>
#include <string>
#include <vector>
#include <list>
#include <catch.hpp>

#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "PKB/PKBRead.h"
#include "QPS/QPS.h"

using namespace pkb;  // NOLINT
using namespace qps;  // NOLINT

using std::vector;
using std::string;

template<typename T>
void SeedPKB(
    PKBWrite &pkb_write,
    vector<T> &data,
    std::function<void(PKBWrite &, T)> pkb_add_function) {
  for (auto d : data) {
    pkb_add_function(pkb_write, d);
  }
}

// Helper method for testing
std::unique_ptr<PKBRead> InitializePKB(
    vector<string> procedures,
    vector<int> stmts,
    vector<int> reads,
    vector<int> prints,
    vector<int> assigns,
    vector<int> calls,
    vector<int> whiles,
    vector<int> ifs,
    vector<string> variables,
    vector<int> constants
) {
  std::unique_ptr<PKBRelationTable> table =
      std::make_unique<PKBRelationTable>();
  PKBWrite pkb_write(std::move(table));

  // Seed testing data
  SeedPKB<string>(
      pkb_write, procedures,
      [](PKBWrite &pkb_write, string p) ->
          void { pkb_write.add_procedure(p); });

  SeedPKB<int>(
      pkb_write, stmts,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_stmt(s); });

  SeedPKB<int>(
      pkb_write, reads,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_read(s); });

  SeedPKB<int>(
      pkb_write, prints,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_print(s); });

  SeedPKB<int>(
      pkb_write, assigns,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_assign(s); });

  SeedPKB<int>(
      pkb_write, calls,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_call(s); });

  SeedPKB<int>(
      pkb_write, whiles,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_while(s); });

  SeedPKB<int>(
      pkb_write, ifs,
      [](PKBWrite &pkb_write, int s) ->
          void { pkb_write.add_if(s); });

  SeedPKB<string>(
      pkb_write, variables,
      [](PKBWrite &pkb_write, string var) ->
          void { pkb_write.add_variable(var); });

  SeedPKB<int>(
      pkb_write, constants,
      [](PKBWrite &pkb_write, int c) ->
          void { pkb_write.add_constant(c); });

  return std::make_unique<PKBRead>(pkb_write.ProcessTableAndEndWrite());
}

// Helper method
void TestQuery(
    QPS &qps, std::unique_ptr<PKBRead> &pkb,
    string query, std::list<string> expected_results) {
  std::list<string> actual_results;
  qps.evaluate(query, actual_results, pkb);
  REQUIRE(util::CompareResults(actual_results, expected_results));
}

TEST_CASE("Test PKB and QPS integration for Select with no clauses") {
  QPS qps;
  std::unique_ptr<PKBRead> pkb = InitializePKB(
      /* procedures */ {"proc1", "proc2"},
      /* stmts */ {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
      /* reads */ {1, 3, 5},
      /* prints */ {2, 4, 6},
      /* assigns */ {7, 9},
      /* calls */ {8, 10},
      /* whiles */ {11},
      /* ifs */  {12},
      /* variables */ {"x", "y", "z"},
      /* constants */ {123, 456, 789});

  SECTION("Get all procedures from PKB") {
    TestQuery(qps, pkb,
              "procedure p; Select p",
              {"proc1", "proc2"});
  }

  SECTION("Get all stmts from PKB") {
    TestQuery(qps, pkb,
              "stmt s; Select s",
              {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"});
  }

  SECTION("Get all reads from PKB") {
    TestQuery(qps, pkb,
              "read r; Select r",
              {"1", "3", "5"});
  }

  SECTION("Get all prints from PKB") {
    TestQuery(qps, pkb,
              "print p; Select p",
              {"2", "4", "6"});
  }

  SECTION("Get all assign from PKB") {
    TestQuery(qps, pkb,
              "assign a; Select a",
              {"7", "9"});
  }

  SECTION("Get all call from PKB") {
    TestQuery(qps, pkb,
              "call c; Select c",
              {"8", "10"});
  }

  SECTION("Get all while from PKB") {
    TestQuery(qps, pkb,
              "while w; Select w",
              {"11"});
  }

  SECTION("Get all if from PKB") {
    TestQuery(qps, pkb,
              "if i; Select i",
              {"12"});
  }

  SECTION("Get all variables from PKB") {
    TestQuery(qps, pkb,
              "variable v; Select v",
              {"x", "y", "z"});
  }

  SECTION("Get all constants from PKB") {
    TestQuery(qps, pkb,
              "constant c; Select c",
              {"123", "456", "789"});
  }

  SECTION("Get all constants and variables from PKB") {
    TestQuery(qps, pkb,
              "constant c; variable v; Select <c, v>",
              {
                  "123, x", "123, y", "123, z",
                  "456, x", "456, y", "456, z",
                  "789, x", "789, y", "789, z"});
  }
}
