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
  static QueryPtr validate(std::unique_ptr<Query> &query);
  static bool DesignEntitySynonyms(QueryPtr &query);
  static bool IsWildcard(QueryPtr &query);
  static bool SynonymCheck(QueryPtr &query);
  static bool isDeclaredOnce(QueryPtr &query);
 private:
  std::vector<std::unique_ptr<Clause>> clauses_;
  std::vector<std::string> synonyms_;
};
}  // namespace qps
