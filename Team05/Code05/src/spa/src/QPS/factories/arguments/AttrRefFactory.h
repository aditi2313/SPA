#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "QPS/models/AttrRef.h"
#include "ArgumentFactory.h"

namespace qps {
class AttrRefFactory : public ArgumentFactory {
 public:
  inline ArgumentPtr Create(std::string token) override {
    auto [syn_name, attr_name] = AttrRef::split_attr_ref(token);
    auto attr_ref_arg = std::make_unique<AttrRefArg>(
        syn_name, AttrRef::get_attr_type(attr_name));
    return attr_ref_arg;
  }

  inline bool CheckSyntax(std::string token) override {
    return AttrRef::is_attr_ref(token);
  }
};
}  // namespace qps
