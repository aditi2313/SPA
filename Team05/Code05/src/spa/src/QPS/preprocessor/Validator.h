#pragma once
#include <QPS/models/Query.h>
#include <common/Exceptions.h>

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
namespace qps {
class Validator {
 public:
  static void Validate(std::unique_ptr<Query> &query);
 private:
  static void ValidateClauseArguments(QueryPtr &query);
  static void ValidateSynonymsDeclaredExactlyOnce(QueryPtr &query);
  static void ValidateSynonymsUsedAreDeclared(QueryPtr &query);
  static void ValidateArgumentSynonym(QueryPtr &query, ArgumentPtr &arg);
};
}  // namespace qps
