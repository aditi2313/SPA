#include <catch.hpp>
#include <memory>

#include "SP/SPTesting.h"
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
