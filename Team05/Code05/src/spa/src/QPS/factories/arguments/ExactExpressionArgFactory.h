#pragma once

#include <utility> 
#include <string>
#include <memory>

#include "ArgumentFactory.h"

namespace qps {
class ExactExpressionArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(std::move(AST), true);
    } catch (std::exception _) {
      throw PqlSyntaxErrorException("Invalid expression");
    }
  }

  inline bool CheckSyntax(std::string token) override {
    // Syntax for expressions are checked when trying
    // to create the AST Tree
    return true;
  }
};

}  // namespace qps
