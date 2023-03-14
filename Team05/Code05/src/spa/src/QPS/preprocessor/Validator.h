#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#include "QPS/models/Query.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class Validator {
 public:
  static void Validate(std::unique_ptr<Query> &query);
 private:
  static void InitializeSynonymEntityTypes(QueryPtr &query);

  static void ValidateClauseArguments(QueryPtr &query);
  static void ValidateSynonymsDeclaredExactlyOnce(QueryPtr &query);
  static void ValidateSynonymsUsedAreDeclared(QueryPtr &query);
  static void ValidateAttrRefs(QueryPtr &query);
};
}  // namespace qps
