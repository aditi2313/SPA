#pragma once

#include <memory>
#include <string>
#include <utility>
#include <catch.hpp>

#include "SP/lexer/Lexer.h"
#include "SP/parser/relations/CondExprParser.h"
#include "SP/parser/relations/RelExprParser.h"
#include "common/exceptions/SP.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/relations/RelExprNode.h"

using namespace ast;  // NOLINT
using namespace sp;   // NOLINT

std::unique_ptr<RelFactor> MakeFactor(std::unique_ptr<ExprNode> expr_node);

std::unique_ptr<VarNode> MakeVar(std::string var_name);
std::unique_ptr<RelFactor> InitialiseAdd();

std::unique_ptr<RelFactor> InitialiseSub();

ExprNodePtr CreateOp(ExprNodePtr left, ExprNodePtr right, Token tok);

ExprNodePtr MakeConst(int);