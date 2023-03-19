#pragma once
#include <memory>
#include <string>
#include <utility>

#include "ArgumentFactory.h"

namespace qps {

class WildcardFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    return std::make_unique<Wildcard>();
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_wildcard(token);
  }
};

}  // namespace qps
