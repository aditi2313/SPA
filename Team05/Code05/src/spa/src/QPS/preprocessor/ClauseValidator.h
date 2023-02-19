#pragma once

#include <string>

#include "QPS/models/PQL.h"
#include "QPS/models/Argument.h"

namespace qps {
class ClauseValidator {
 public:
  static void ValidateClauseArgumentTypes(
      PQL::RelName rel_name, ArgumentPtr &arg1, ArgumentPtr &arg2);

 private:
  static inline void ThrowException(PQL::RelName rel_name) {
    std::string msg = "Invalid argument types in " + rel_name;
    throw PqlSyntaxErrorException(msg.c_str());
  }
};
}  // namespace qps
