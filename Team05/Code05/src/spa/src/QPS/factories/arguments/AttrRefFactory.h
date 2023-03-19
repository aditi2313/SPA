#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ArgumentFactory.h"

namespace qps {
class AttrRefFactory : public ArgumentFactory {
public:
  inline ArgumentPtr Create(std::string token) override {
      auto [syn_name, attr_name] = PQL::split_attr_ref(token);
      auto syn_arg = std::make_unique<SynonymArg>(syn_name);
      syn_arg->set_attr_name(attr_name);
      return syn_arg;
  }

  inline bool CheckSyntax(std::string token) override {
      return PQL::is_attr_ref(token);
  }
};
}  // namespace qps
