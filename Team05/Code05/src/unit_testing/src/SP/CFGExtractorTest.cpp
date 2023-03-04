#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/CFGExtractor.h"
#include "models/CFG/CFGNode.h"

using namespace cfg;  // NOLINT
using namespace sp;   // NOLINT

void TestExtractingCFG(CFG& cfg, std::unordered_map<int, int> expected) {
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
  auto cfg = program->add_procedure("proc");
  cfg.AddChild(cfg.get_root(), 1, 5);
  TestExtractingCFG(cfg, {{1, 2}, {2, 3}, {3, 4}, {4, 5}});
  
}
