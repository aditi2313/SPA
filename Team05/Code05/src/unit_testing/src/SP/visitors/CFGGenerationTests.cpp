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
  REQUIRE(cfg.GetSecondChild(if1) == res->get_node(6));
  
  auto& w1 = res->get_node(1);
  REQUIRE(cfg.GetSecondChild(w1) == res->get_node(7));
  REQUIRE(!w1.is_empty());

  // test for connection from stmt list back to parent
  auto& else1 = res->get_node(6);
  auto& end1 = cfg.GetFirstChild(else1);
  auto& end2 = cfg.GetFirstChild(end1);
  REQUIRE(end1.is_empty());
  REQUIRE(end2.is_empty());
  REQUIRE(cfg.GetFirstChild(end2) == w1);


}
