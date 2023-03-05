#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/CFGExtractor.h"
#include "models/CFG/CFGNode.h"

using namespace cfg;  // NOLINT
using namespace sp;   // NOLINT

void TestExtractingCFG(CFG& cfg, std::vector<std::pair<int, int>> expected) {
  // initialise expected
  auto expected_table = std::make_unique<pkb::PKBRelationTable>();
  auto w = std::make_unique<pkb::PKBWrite>(std::move(expected_table));
  for (auto& [l, n] : expected) {
    w->AddNextData(l, n);
  }
  expected_table = w->EndWrite();

  // initialise result
  std::unique_ptr<pkb::PKBRelationTable> rel_table =
      std::make_unique<pkb::PKBRelationTable>();
  std::unique_ptr<pkb::PKBWrite> writer =
      std::make_unique<pkb::PKBWrite>(std::move(rel_table));
  CFGExtractor extractor(std::move(writer));
  extractor.WriteNext(cfg.get_root(), cfg);
  writer = extractor.EndVisit();

  rel_table = writer->EndWrite();

  REQUIRE(*rel_table == *expected_table);
}

TEST_CASE("Simple cfg extracted") {
  // construction of cfg
  std::unique_ptr<ProgramCFG> program = std::make_unique<ProgramCFG>();
  CFG& cfg = program->add_procedure("proc");
  cfg.AddChild(cfg.get_root(), 1, 5);
  TestExtractingCFG(cfg, {{1, 2}, {2, 3}, {3, 4}, {4, 5}});
}

TEST_CASE("CFG with loops extracted") {
  ProgramCFG program;

  CFG& cfg = program.add_procedure("proc");
  auto& c1 = cfg.AddChild(cfg.get_root(), 1, 5);

  auto& c2 = cfg.AddChild(c1, 6, 10);
  cfg.AddChild(c2, c1);
  cfg.AddChild(c2, 11, 15);
  TestExtractingCFG(cfg, {{1, 2},
                          {2, 3},
                          {3, 4},
                          {4, 5},
                          {5, 6},
                          {6, 7},
                          {7, 8},
                          {8, 9},
                          {9, 10},
                          {10, 1},
                          {10, 11},
                          {11, 12},
                          {12, 13},
                          {13, 14},
                          {14, 15}});
}

TEST_CASE("Test on simple branching") {
  ProgramCFG program;
  CFG& cfg = program.add_procedure("proc");
  auto& c1 = cfg.AddChild(cfg.get_root(), 1, 1);
  auto& c2 = cfg.AddChild(c1, 2, 2);
  auto& c3 = cfg.AddChild(c1, 3, 3);

  TestExtractingCFG(cfg, {{1, 2}, {1, 3}});
}

TEST_CASE("Test on branching with loops and empty nodes") {
  ProgramCFG program;
  CFG& cfg = program.add_procedure("proc");
  auto& c1 = cfg.AddChild(cfg.get_root(), 1, 1);
  auto& c2 = cfg.AddChild(c1, 2, 2);
  auto& c3 = cfg.AddChild(c1, 3, 3);
  auto& c4 = cfg.AddChild(c3, 4, 4);
  cfg.AddChild(c4, c3);
  auto& empt = cfg.AddNode();
  cfg.AddChild(c4, empt);
  cfg.AddChild(empt, c3);  
  TestExtractingCFG(cfg, {{1, 2}, {1, 3}, {3, 4}, {4, 3}});
}
