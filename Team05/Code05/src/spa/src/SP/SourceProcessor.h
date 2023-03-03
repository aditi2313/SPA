#pragma once

#include <memory>
#include <string>
#include <utility>

#include "../models/AST/factor_node/FactorNode.h"
#include "SP/parser/ProgramParser.h"
#include "SP/validators/ProgramValidator.h"
#include "SP/visitors/AssignVisitor.h"
#include "SP/visitors/DataVisitor.h"
#include "SP/visitors/FollowsVisitor.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "SP/visitors/ParentVisitor.h"
#include "SP/visitors/UsesVisitor.h"
#include "lexer/Lexer.h"
#include "models/AST/ProgramNode.h"
#include "parser/expression/ExpressionParser.h"

namespace sp {

// Facade class that serves as entry point for other components
class SourceProcessor {
 public:
  static std::unique_ptr<ast::ExprNode> ParseExpression(std::string expr) {
    sp::Lexer lxr(std::move(expr));
    sp::ExpressionParser exp_parser;
    return exp_parser.parse(lxr);
  }

  static std::unique_ptr<ast::ProgramNode> ParseProgram(std::string program) {
    sp::Lexer lxr(std::move(program));
    sp::ProgramParser program_parser;
    auto root = program_parser.parse(lxr);

    auto validator = ProgramValidator(root);
    validator.Validate();

    return root;
  }

  static void ExtractRelationships(std::unique_ptr<ast::ProgramNode> &root,
      std::unique_ptr<pkb::PKBRelationTable> &pkb_relation) {
    auto writer = std::make_unique<pkb::PKBWrite>(std::move(pkb_relation));

    sp::AssignVisitor av(std::move(writer));
    root->AcceptVisitor(&av);
    writer = av.EndVisit();

    sp::DataVisitor dv(std::move(writer));
    root->AcceptVisitor(&dv);
    writer = dv.EndVisit();

    sp::ModifiesVisitor mv(std::move(writer));
    root->AcceptVisitor(&mv);
    writer = mv.EndVisit();

    sp::ParentVisitor pv(std::move(writer));
    root->AcceptVisitor(&pv);
    writer = pv.EndVisit();

    sp::UsesVisitor uv(std::move(writer));
    root->AcceptVisitor(&uv);
    writer = uv.EndVisit();

    sp::FollowsVisitor fv(std::move(writer));
    root->AcceptVisitor(&fv);
    writer = fv.EndVisit();

    pkb_relation = writer->ProcessTableAndEndWrite();
  }
};

using ExprNodePtr = std::unique_ptr<ast::ExprNode>;
}  // namespace sp
