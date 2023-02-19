#include <catch.hpp>

#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "common/filter/filters/PredicateFilter.h"
#include "models/AST/factor_node/FactorNode.h"

TEST_CASE("Assign Filter test") {
  SECTION("Expression filter test") {
    std::unique_ptr<ast::VarNode> var1 = std::make_unique<ast::VarNode>("y");
    std::unique_ptr<ast::ConstNode> const1 =
        std::make_unique<ast::ConstNode>(1);
    std::unique_ptr<ast::ConstNode> const2 =
        std::make_unique<ast::ConstNode>(2);
    std::unique_ptr<ast::ConstNode> const3 =
        std::make_unique<ast::ConstNode>(3);
    std::unique_ptr<ast::OpNode> minus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokMinus, std::move(const2), std::move(const3));
    std::unique_ptr<ast::ExprNode> plus1 = std::make_unique<ast::OpNode>(
        sp::Token::kTokPlus, std::move(minus1), std::move(const1));

    auto plus2 = plus1->Copy();
    auto plus3 = plus2->Copy();
    auto plus4 = plus3->Copy();

    std::unique_ptr<pkb::PKBRelationTable> table =
        std::make_unique<pkb::PKBRelationTable>();
    pkb::PKBWrite writer(std::move(table));
    writer.AddAssignData("v", 3, std::move(plus2));
    writer.AddAssignData("v", 5, std::move(plus3));
    writer.AddAssignData("v", 7, std::move(plus4));
    table = writer.EndWrite();

    pkb::PKBRead reader(std::move(table));
    auto result =
        reader.Assigns(std::make_unique<filter::AssignPredicateFilter>(
            [&](auto data) { return data.TestExpression(plus1, true); }));
  }
}
