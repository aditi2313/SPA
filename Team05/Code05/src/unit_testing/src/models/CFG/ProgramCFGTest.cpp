#include <catch.hpp>
#include <unordered_set>

#include "models/CFG/CFG.h"
#include "models/CFG/ProgramCFG.h"

using namespace cfg;  // NOLINT

TEST_CASE("Simple construction of cfg") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto root = cfg.get_root();

  std::vector<int> lines{1, 2, 3};
  auto c = cfg.AddChild(root, lines);

  REQUIRE(!c.HasFirstChild());
  REQUIRE(!c.HasSecondChild());
  REQUIRE(c.is_end());
  std::vector<int> lines2{4, 5, 6};
  auto c_child = cfg.AddChild(c, lines2);

  REQUIRE(c.HasFirstChild());
  REQUIRE(!c.HasSecondChild());
  REQUIRE(!c.is_end());
}

TEST_CASE("Construction of cfg with while loop") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto root = cfg.get_root();
  std::vector<int> lines{1, 2, 3};
  std::vector<int> lines2{4, 5, 6};
  auto c = cfg.AddChild(root, lines);
  auto c_child = cfg.AddChild(c, lines2);

  cfg.AddChild(c_child, c);
  REQUIRE(c.HasFirstChild());
  REQUIRE(!c.HasSecondChild());
  REQUIRE(c_child.HasFirstChild());
  REQUIRE(!c_child.HasSecondChild());
  REQUIRE(c_child == cfg.GetFirstChild(c));
}
