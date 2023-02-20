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
  static void ValidateClauseArguments(QueryPtr &query);
  static void ValidateSynonymsDeclaredExactlyOnce(QueryPtr &query);
  static void ValidateSynonymsUsedAreDeclared(QueryPtr &query);
  static void ValidateArgumentSynonymDeclared(
      QueryPtr &query, ArgumentPtr &arg);
  static void ValidateArgumentSynonymType(ArgumentPtr &arg,
                                          EntityName expected_entity_name,
                                          bool is_exact_match);
};
}  // namespace qps
