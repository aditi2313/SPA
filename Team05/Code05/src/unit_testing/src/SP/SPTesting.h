#pragma once

#include <memory>
#include <string>
#include <utility>
#include <catch.hpp>

#include "SP/lexer/Lexer.h"
#include "SP/parser/relations/CondExprParser.h"
#include "SP/parser/relations/RelExprParser.h"
#include "common/exceptions/SPExceptions.h"
#include "models/AST/ProcNode.h"
#include "models/AST/ProgramNode.h"
#include "models/AST/factor_node/FactorNode.h"
#include "models/AST/relations/CondExprNode.h"
#include "models/AST/relations/RelExprNode.h"
#include "models/AST/stmt_node/StmtNode.h"

using namespace ast;  // NOLINT
using namespace sp;   // NOLINT

std::unique_ptr<RelFactor> MakeFactor(std::unique_ptr<ExprNode> expr_node);

std::unique_ptr<VarNode> MakeVar(std::string var_name);
std::unique_ptr<RelFactor> InitialiseAdd();

std::unique_ptr<RelFactor> InitialiseSub();

ExprNodePtr CreateOp(ExprNodePtr left, ExprNodePtr right, Token tok);

ExprNodePtr MakeConst(int);

std::unique_ptr<ReadNode> MakeRead(std::string var_name, int);
std::unique_ptr<PrintNode> MakePrint(std::string var_name, int line);
std::unique_ptr<AndExprNode> MakeAnd(std::string left, std::string right);
std::unique_ptr<IfNode> MakeIf(int line, int s1, int e1, int s2, int e2);
std::unique_ptr<WhileNode> MakeWhile(int line, int, int);
