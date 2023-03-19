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
    auto attr_ref_arg = std::make_unique<AttrRefArg>(
        syn_name, PQL::get_attr_type(attr_name));
    return attr_ref_arg;
  }

  inline bool CheckSyntax(std::string token) override {
    return PQL::is_attr_ref(token);
  }
};
}  // namespace qps
