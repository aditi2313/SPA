#pragma once

#include <memory>
#include <string>
#include <utility>

#include "ArgumentFactory.h"

namespace qps {

class SynonymArgFactory : public ArgumentFactory {
public:
  inline ArgumentPtr Create(std::string token) override {
      return std::make_unique<SynonymArg>(token);
  }

  inline bool CheckSyntax(std::string token) override {
      return PQL::is_ident(token);
  }
};
}  // namespace qps
