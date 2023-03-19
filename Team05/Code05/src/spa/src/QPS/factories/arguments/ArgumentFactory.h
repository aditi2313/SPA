#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

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

using ArgumentFactoryPtr = std::unique_ptr<ArgumentFactory>;

}  // namespace qps
