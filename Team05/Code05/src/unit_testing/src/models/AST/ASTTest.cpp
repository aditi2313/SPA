#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <catch.hpp>

#include "models/AST/TNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/stmt_node/StmtNode.h"

void require(bool b) { REQUIRE(b); }

TEST_CASE("1st Test") {
  std::unique_ptr<ast::VarNode> c1 = std::make_unique<ast::VarNode>("test");
  std::unique_ptr<ast::ReadNode> c2 =
      std::make_unique<ast::ReadNode>(std::move(c1), 2);

  require(1 == 1);
}