#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <utility>
#include <memory>

#include "PKB/PKBRead.h"
#include "QPS/models/arguments/Export.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ArgumentFactory {
 public:
  ArgumentFactory() {}

  virtual ArgumentPtr Create(std::string token) = 0;
  virtual bool CheckSyntax(std::string token) = 0;

  virtual ~ArgumentFactory() = default;
};

class AttrRefFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    auto [syn_name, attr_name] = PQL::split_attr_ref(token);
    return std::make_unique<AttrRefArg>(syn_name, attr_name);
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_attr_ref(token);
  }
};

class ExactExpressionArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(
          std::move(AST), true);
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

class WildcardExpressionArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    try {
      auto AST = sp::SourceProcessor::ParseExpression(token);
      return std::make_unique<ExpressionArg>(
          std::move(AST), false);
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

class IdentArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    return std::make_unique<IdentArg>(token);
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_ident(token);
  }
};

class IntegerArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    return std::make_unique<IntegerArg>(stoi(token));
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_integer(token);
  }
};

class SynonymArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    return std::make_unique<SynonymArg>(token);
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_ident(token);
  }
};

class WildcardFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    return std::make_unique<Wildcard>();
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_wildcard(token);
  }
};

using ArgumentFactoryPtr = std::unique_ptr<ArgumentFactory>;
}  // namespace qps
