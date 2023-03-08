#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "models/CFG/CFG.h"
#include "models/CFG/ProgramCFG.h"

using namespace cfg;  // NOLINT

void TestGettingLineNumber(std::vector<int> lines, int start, int end);

TEST_CASE("Simple construction of cfg") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto& root = cfg.get_root();

  auto& c = cfg.AddChild(root, 1, 3);

  REQUIRE(!c.HasFirstChild());
  REQUIRE(!c.HasSecondChild());
  REQUIRE(c.is_end());
  auto& c_child = cfg.AddChild(c, 4, 6);

  REQUIRE(c.HasFirstChild());
  REQUIRE(!c.HasSecondChild());
  REQUIRE(!c.is_end());
}

TEST_CASE("Construction of cfg with while loop") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto& root = cfg.get_root();

  auto& c = cfg.AddChild(root, 1, 2);
  auto& c_child = cfg.AddChild(c, 3, 5);

  cfg.AddChild(c_child, c);
  REQUIRE(c.HasFirstChild());
  REQUIRE(!c.HasSecondChild());
  REQUIRE(c_child.HasFirstChild());
  REQUIRE(!c_child.HasSecondChild());
  REQUIRE(c_child == cfg.GetFirstChild(c));
}

TEST_CASE("Construction of cfg with branching") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto& root = cfg.get_root();

  auto& c1 = cfg.AddChild(root, 1, 1);
  auto& c2 = cfg.AddChild(c1, 2, 2);
  auto& c3 = cfg.AddChild(c1, 3, 3);

  REQUIRE(c1.HasSecondChild());
  REQUIRE(c1.HasFirstChild());
  REQUIRE(!c1.is_end());
}

TEST_CASE("Construction of cfg with loop order and branching") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple_proc");
  auto& root = cfg.get_root();

  auto& c1 = cfg.AddChild(root, 1, 4);
  auto& c2 = cfg.AddChild(c1, 5, 10);
  cfg.AddChild(c2, c1);

  auto& c3 = cfg.AddChild(c1, 11, 15);
  auto& c4 = cfg.AddChild(c3, 16, 17);
  auto& c5 = cfg.AddChild(c3, 18, 19);

  REQUIRE(c4.is_end());
  REQUIRE(c5.is_end());
  REQUIRE(c1.HasSecondChild());
  REQUIRE(c2.HasFirstChild());
  REQUIRE(cfg.GetFirstChild(c1) == c2);
}

TEST_CASE("Construction of line from start and end") {
  SECTION("Construction of line for same number") {
    TestGettingLineNumber({2}, 2, 2);
  }
  SECTION("Construction of line for different numbers") {
    TestGettingLineNumber({1, 2, 3, 4}, 1, 4);
  }
}

TEST_CASE("Test line number map in program cfg") {
  ProgramCFG program_cfg;
  auto& cfg = program_cfg.add_procedure("simple");
  auto& cnode1 = cfg.AddChild(cfg.get_root(), 1, 5);
  auto& cnode2 = cfg.AddChild(cnode1, 6, 8);

  SECTION("Program cfg query start") {
    REQUIRE(program_cfg.get_node(1) == cnode1);
    REQUIRE(program_cfg.get_node(6) == cnode2);
  }

  SECTION("Program cfg query end") {
    REQUIRE(program_cfg.get_node(5) == cnode1);
    REQUIRE(program_cfg.get_node(8) == cnode2);
  }

  SECTION("Program cfg query middle") {
    REQUIRE(program_cfg.get_node(3) == cnode1);
    REQUIRE(program_cfg.get_node(7) == cnode2);
  }
}

void TestGettingLineNumber(std::vector<int> lines, int start, int end) {
  ProgramCFG prog_cfg;
  auto& cfg = prog_cfg.add_procedure("some_proc");
  auto& root = cfg.get_root();
  auto& c1 = cfg.AddChild(root, start, end);
  auto result = c1.get_lines();
  REQUIRE(result == lines);

  auto& other_root = cfg.get_root();
  REQUIRE(other_root.HasFirstChild());
}
