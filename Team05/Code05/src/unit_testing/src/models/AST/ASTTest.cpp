#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <catch.hpp>

#include "PKB/PKBWrite.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "SP/visitors/AssignVisitor.h"
#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/stmt_node/StmtNode.h"

void require(bool b) { REQUIRE(b); }

TEST_CASE("1st Test") {
  std::unique_ptr<ast::VarNode> c1 = std::make_unique<ast::VarNode>("test");
  std::unique_ptr<ast::ReadNode> c2 =
      std::make_unique<ast::ReadNode>(std::move(c1), 2);
  std::unique_ptr<ast::ConstNode> c3 = std::make_unique<ast::ConstNode>(5);
  std::unique_ptr<ast::VarNode> c4 = std::make_unique<ast::VarNode>("x");
  ast::AssignNode c5 = ast::AssignNode(std::move(c4), std::move(c3), 1);
  // TODO(nhjryan): move this to integration testing folder later
  std::unique_ptr<pkb::PKBRelationTable> p1 =
      std::make_unique<pkb::PKBRelationTable>();
  std::unique_ptr<pkb::PKBWrite> p2 =
      std::make_unique<pkb::PKBWrite>(std::move(p1));
  sp::ModifiesVisitor mv(std::move(p2));
  mv.VisitAssign(&c5);

  std::unique_ptr<ast::VarNode> var1 = std::make_unique<ast::VarNode>("y");
  std::unique_ptr<ast::ConstNode> const1 = std::make_unique<ast::ConstNode>(1);
  std::unique_ptr<ast::ConstNode> const2 = std::make_unique<ast::ConstNode>(2);
  std::unique_ptr<ast::ConstNode> const3 = std::make_unique<ast::ConstNode>(3);
  std::unique_ptr<ast::MinusNode> minus1 =
      std::make_unique<ast::MinusNode>(std::move(const2), std::move(const3));
  std::unique_ptr<ast::PlusNode> plus1 =
      std::make_unique<ast::PlusNode>(std::move(minus1), std::move(const1));
  ast::AssignNode assign1 = ast::AssignNode(std::move(var1), std::move(plus1), 3);
  sp::AssignVisitor av(std::move(mv.EndVisit()));
  av.VisitAssign(&assign1);

  require(1 == 1);
}
