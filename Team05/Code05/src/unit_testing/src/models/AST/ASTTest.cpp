#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <catch.hpp>

#include "PKB/PKBWrite.h"
#include "SP/visitors/AssignVisitor.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/stmt_node/StmtNode.h"

void require(bool b) { REQUIRE(b); }

TEST_CASE("1st Test") {
  SECTION("Test Vistor") {
    std::unique_ptr<ast::VarNode> c1 = std::make_unique<ast::VarNode>("test");
    std::unique_ptr<ast::ReadNode> c2 =
        std::make_unique<ast::ReadNode>(std::move(c1), 2);
    std::unique_ptr<ast::ConstNode> c3 = std::make_unique<ast::ConstNode>(5);
    std::unique_ptr<ast::VarNode> c4 = std::make_unique<ast::VarNode>("x");
    ast::AssignNode c5 = ast::AssignNode(std::move(c4), std::move(c3), 1);
    std::unique_ptr<pkb::PKBRelationTable> p1 =
        std::make_unique<pkb::PKBRelationTable>();
    std::unique_ptr<pkb::PKBWrite> p2 =
        std::make_unique<pkb::PKBWrite>(std::move(p1));
    sp::ModifiesVisitor mv(std::move(p2));
    mv.VisitAssign(&c5);

    std::unique_ptr<ast::VarNode> var1 = std::make_unique<ast::VarNode>("y");
    std::unique_ptr<ast::ConstNode> const1 =
        std::make_unique<ast::ConstNode>(1);
    std::unique_ptr<ast::ConstNode> const2 =
        std::make_unique<ast::ConstNode>(2);
    std::unique_ptr<ast::ConstNode> const3 =
        std::make_unique<ast::ConstNode>(3);
    std::unique_ptr<ast::OpNode> minus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokMinus, std::move(const2), std::move(const3));
    std::unique_ptr<ast::OpNode> plus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokPlus, std::move(minus1), std::move(const1));
    ast::AssignNode assign1 =
        ast::AssignNode(std::move(var1), std::move(plus1), 3);
    sp::AssignVisitor av(std::move(mv.EndVisit()));
    av.VisitAssign(&assign1);
  }

  SECTION("Test Equals") {
    std::unique_ptr<ast::VarNode> var1 = std::make_unique<ast::VarNode>("y");
    std::unique_ptr<ast::ConstNode> const1 =
        std::make_unique<ast::ConstNode>(1);
    std::unique_ptr<ast::ConstNode> const2 =
        std::make_unique<ast::ConstNode>(2);
    std::unique_ptr<ast::ConstNode> const3 =
        std::make_unique<ast::ConstNode>(3);
    std::unique_ptr<ast::OpNode> minus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokMinus, std::move(const2), std::move(const3));
    std::unique_ptr<ast::OpNode> plus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokPlus, std::move(minus1), std::move(const1));
    auto other = plus1->Copy();
    REQUIRE(other->DeepEquals(*plus1));
    std::unique_ptr<ast::ConstNode> c2 = std::make_unique<ast::ConstNode>(2);
    REQUIRE(!other->DeepEquals(*c2));
  }

  SECTION("Test all Equals") {
    ast::ConstNode const_1(1);
    ast::ConstNode const_2(2);
    ast::ConstNode const_3(1);
    REQUIRE(!const_1.DeepEquals(const_2));
    REQUIRE(const_1.DeepEquals(const_3));

    ast::VarNode var_1("v");
    ast::VarNode var_2("d");
    ast::VarNode var_3("v");
    REQUIRE(!var_1.DeepEquals(var_2));
    REQUIRE(var_1.DeepEquals(var_3));
    REQUIRE(!var_1.DeepEquals(const_1));
  }

  SECTION("Minus testing") {
    std::unique_ptr<ast::ConstNode> const2 =
        std::make_unique<ast::ConstNode>(2);
    std::unique_ptr<ast::ConstNode> const3 =
        std::make_unique<ast::ConstNode>(3);
    std::unique_ptr<ast::OpNode> minus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokMinus, std::move(const2), std::move(const3));
    const2 = std::make_unique<ast::ConstNode>(2);
    const3 = std::make_unique<ast::ConstNode>(3);
    REQUIRE(!const2->DeepEquals(*minus1));
    REQUIRE(!const3->DeepEquals(*minus1));
    std::unique_ptr<ast::OpNode> m3 = std::make_unique<ast::OpNode>(
        sp::Token::kTokMinus, std::move(const2), std::move(const3));
    REQUIRE(m3->DeepEquals(*minus1));
  }
}
