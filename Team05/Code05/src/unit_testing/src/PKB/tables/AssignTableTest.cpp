#include <string>
#include <catch.hpp>

#include "PKB/data/AssignData.h"
#include "PKB/tables/IndexableTable.h"

using namespace pkb;  // NOLINT

TEST_CASE("Test AssignTable") {
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

    AssignData assign_data("v", 3, std::move(plus1));

    AssignTable assign_table;
    assign_table.add_row(5, assign_data);

    SECTION("Checking if AssignTable row exists") {
        REQUIRE(assign_table.exists(5));
    };

    SECTION("Checking if AssignTable is empty") {
        REQUIRE(!assign_table.empty());
    };

    SECTION("Retrieving AssignTable row") {
        AssignData retrieved_assign_data = assign_table.get_row(5);
        bool line_check = retrieved_assign_data.get_line() == 3;
        bool variable_check = retrieved_assign_data.get_variable() == "v";
        REQUIRE((line_check && variable_check));
    };
}
