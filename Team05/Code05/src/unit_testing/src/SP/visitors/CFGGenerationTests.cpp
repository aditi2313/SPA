#include <memory>
#include <catch.hpp>

#include "SP/SPTesting.h"
#include "SP/SourceProcessor.h"
#include "SP/visitors/CFGGeneratingVisitor.h"

using namespace sp;   // NOLINT
using namespace ast;  // NOLINT

TEST_CASE("Test construction of cfg on basic ast") {
  auto read_node = MakeRead("v", 1);
  auto print_node = MakePrint("v", 2);
  auto stmt_list = std::make_unique<StmtLstNode>(std::move(read_node));
  stmt_list->add_stmt(std::move(print_node));

  auto proc = std::make_unique<ProcNode>("proc", std::move(stmt_list));
  auto prog = std::make_unique<ProgramNode>(std::move(proc));

  CFGGeneratingVisitor visitor;
  visitor.VisitProgram(prog.get());
  auto res = visitor.CreateCFG();

  auto cfg = res->get_cfg("proc");
  cfg.GetFirstChild(cfg.get_root());
}

// TODO(Gab) consider more specific methods of constructing test cases instead
// of relying on sp parse program
TEST_CASE("Test construction of cfg on if ast") {
  auto ast = SourceProcessor::ParseProgram(
      "procedure "
      "procedure {"
      "if (x <= 100) then {"
      "read x;"
      "print y;"
      "if (y < 100) then { read x; } else { print y; }"
      "} else { read x; }"
      "a = x + 1;"
      "}");

  CFGGeneratingVisitor visitor;
  visitor.VisitProgram(ast.get());
  auto res = visitor.CreateCFG();

  auto cfg = res->get_cfg("procedure");
  auto& if1 = res->get_node(4);
  REQUIRE(cfg.GetSecondChild(if1) == res->get_node(6));
}

TEST_CASE("Test construction of cfg on while ast") {
  auto ast = SourceProcessor::ParseProgram(
      "procedure "
      "procedure {"
      "while (x <= 100) {"
      "read x;"
      "print y;"
      "if (y < 100) then { read x; } else { print y; }"
      "}"
      "a = x + 1;"
      "}");

  CFGGeneratingVisitor visitor;
  visitor.VisitProgram(ast.get());
  auto res = visitor.CreateCFG();

  auto cfg = res->get_cfg("procedure");
  auto& if1 = res->get_node(4);
  auto& w1 = res->get_node(1);

  SECTION("Test else branch of if") {
    REQUIRE(cfg.GetSecondChild(if1) == res->get_node(6));
  }

  SECTION("Test while follows statement") {
    REQUIRE(cfg.GetSecondChild(w1) == res->get_node(7));
    REQUIRE(!w1.is_empty());
  }

  SECTION("Connection between else and end nodes") {
    auto& else1 = res->get_node(6);
    auto& end1 = cfg.GetFirstChild(else1);
    auto& end2 = cfg.GetFirstChild(end1);
    REQUIRE(end1.is_empty());
    REQUIRE(end2.is_empty());
    auto& alt_a = cfg.GetFirstChild(end2);
    REQUIRE(alt_a == w1);

    auto& alt_assign = cfg.GetSecondChild(w1);
    REQUIRE(alt_assign == res->get_node(7));
  }
}

TEST_CASE("Test construction of very nested while loops") {
  auto ast = SourceProcessor::ParseProgram(
      "procedure "
      "read {"
      "while (x < 100){"
      "while (x < 100) {"
      "while (x < 100) {"
      "while (x < 100) {"
      "print x;"
      "x = x + 1;"
      "}"
      "print x;"
      "}"
      "print x;"
      "}"
      "print x;"
      "}"
      "print x;"
      "}");
  CFGGeneratingVisitor visitor;
  visitor.VisitProgram(ast.get());
  auto res = visitor.CreateCFG();
  auto cfg = res->get_cfg("read");
  auto print_x = res->get_node(5);
  auto print_x2 = res->get_node(7);
  auto assign_x = res->get_node(6);
  auto end_x = cfg.GetFirstChild(print_x);

  auto w1 = res->get_node(1);
  auto w2 = res->get_node(2);
  auto w3 = res->get_node(3);
  auto w4 = res->get_node(4);
  REQUIRE(print_x == assign_x);

  SECTION("Test stmtlist in while goes back to while node") {
    REQUIRE(end_x == res->get_node(4));
  }
  SECTION("Test stmtlist after while is second child") {
    REQUIRE(cfg.GetSecondChild(w3) == res->get_node(8));
  }
  SECTION("Test non empty children of the end of a while loop") {
    auto non_empty = cfg.GetNonEmptyChildren(print_x2);
    REQUIRE(*non_empty.at(0) == w3);
    REQUIRE(non_empty.size() == 1);
  }

  SECTION("Test non empty children of the end of a while") {
    auto non_empty = cfg.GetNonEmptyChildren(w4);
    REQUIRE(*non_empty.at(0) == res->get_node(5));
    REQUIRE(*non_empty.at(1) == res->get_node(7));
  }
}
