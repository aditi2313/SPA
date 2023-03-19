#pragma once

#include "ArgumentFactory.h"

namespace qps {

class IdentArgFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    return std::make_unique<IdentArg>(token);
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_ident(token);
  }
};
}  // namespace qps
