#pragma once

#include <memory>
#include <string>
#include <utility>

#include "../models/AST/factor_node/FactorNode.h"
#include "SP/CFGExtractor.h"
#include "SP/parser/ProgramParser.h"
#include "SP/validators/ProgramValidator.h"
#include "SP/visitors/AssignVisitor.h"
#include "SP/visitors/CallsVisitor.h"
#include "SP/visitors/DataVisitor.h"
#include "SP/visitors/FollowsVisitor.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "SP/visitors/ParentVisitor.h"
#include "SP/visitors/UsesVisitor.h"
#include "common/logging/Logger.h"
#include "lexer/Lexer.h"
#include "models/AST/ProgramNode.h"
#include "parser/expression/ExpressionParser.h"
#include "visitors/CFGGeneratingVisitor.h"

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
    logging::Logger::Start();
    sp::Lexer lxr(std::move(program));
    sp::ProgramParser program_parser;
    auto root = program_parser.parse(lxr);

    auto validator = ProgramValidator(root);
    validator.Validate();
    logging::Logger::LogAndStop("End parsing program");

    return root;
  }

  static void ExtractRelationships(
      std::unique_ptr<ast::ProgramNode> &root,
      std::unique_ptr<pkb::PKBRelationTable> &pkb_relation) {
    logging::Logger::Start();
    auto writer = std::make_unique<pkb::PKBWrite>(std::move(pkb_relation));

    logging::Logger::Start();
    sp::AssignVisitor av(std::move(writer));
    root->AcceptVisitor(&av);
    writer = av.EndVisit();
    logging::Logger::LogAndStop("Assign visitor finished");

    logging::Logger::Start();
    sp::DataVisitor dv(std::move(writer));
    root->AcceptVisitor(&dv);
    writer = dv.EndVisit();
    logging::Logger::LogAndStop("Data visitor finished");

    logging::Logger::Start();
    sp::ModifiesVisitor mv(std::move(writer));
    root->AcceptVisitor(&mv);
    writer = mv.EndVisit();
    logging::Logger::LogAndStop("Modifies visitor finished");

    logging::Logger::Start();
    sp::ParentVisitor pv(std::move(writer));
    root->AcceptVisitor(&pv);
    writer = pv.EndVisit();
    logging::Logger::LogAndStop("Parent visitor finished");

    logging::Logger::Start();
    sp::UsesVisitor uv(std::move(writer));
    root->AcceptVisitor(&uv);
    writer = uv.EndVisit();
    logging::Logger::LogAndStop("Uses visitor finished");

    logging::Logger::Start();
    sp::FollowsVisitor fv(std::move(writer));
    root->AcceptVisitor(&fv);
    writer = fv.EndVisit();
    logging::Logger::LogAndStop("Follows visitor finished");

    logging::Logger::Start();
    sp::CallsVisitor cv(std::move(writer));
    root->AcceptVisitor(&cv);
    writer = cv.EndVisit();
    logging::Logger::LogAndStop("Calls visitor finished");

    logging::Logger::Start();
    sp::CFGGeneratingVisitor cfg_generator;
    cfg_generator.VisitProgram(root.get());
    auto cfg = cfg_generator.CreateCFG();
    logging::Logger::LogAndStop("Cfg generation finished");

    logging::Logger::Start();
    sp::CFGExtractor cfg_extractor(std::move(writer));
    cfg_extractor.WriteCFG(*cfg);
    writer = cfg_extractor.EndVisit();
    logging::Logger::LogAndStop("Cfg extraction finished");

    pkb_relation = writer->ProcessTableAndEndWrite();
    logging::Logger::LogAndStop("End pkb writing");
  }
};

using ExprNodePtr = std::unique_ptr<ast::ExprNode>;
}  // namespace sp
