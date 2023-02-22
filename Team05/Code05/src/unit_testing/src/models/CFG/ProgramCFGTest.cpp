#include <unordered_set>
#include <catch.hpp>

#include "models/CFG/CFG.h"
#include "models/CFG/ProgramCFG.h"

using namespace cfg;  // NOLINT

TEST_CASE("Simple construction of cfg") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto root = cfg.get_root();

  std::vector<int> lines{1, 2, 3};
  auto c = cfg.AddChild(root, lines);

  REQUIRE(!c->HasFirstChild());
  REQUIRE(!c->HasSecondChild());
  REQUIRE(c->is_end());

  auto c_child = std::make_shared<CFGNode>();
  cfg.AddChild(c, c_child);

  REQUIRE(c->HasFirstChild());
  REQUIRE(!c->HasSecondChild());
  REQUIRE(!c->is_end());
}

TEST_CASE("Construction of cfg with while loop") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto root = cfg.get_root();
  std::vector<int> lines{1, 2, 3};
  auto c = cfg.AddChild(root, lines);
  auto c_child = std::make_shared<CFGNode>();
  cfg.AddChild(c, c_child);
  cfg.AddChild(c_child, c);
  REQUIRE(c->HasFirstChild());
  REQUIRE(!c->HasSecondChild());
  REQUIRE(c_child->HasFirstChild());
  REQUIRE(!c_child->HasSecondChild());
  REQUIRE(c_child == c->get_first_child().lock());

}
