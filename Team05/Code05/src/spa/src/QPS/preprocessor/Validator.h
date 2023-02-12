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
  static bool validate(std::unique_ptr<Query> &query);
  bool DesignEntitySynonyms(std::vector<std::unique_ptr<Clause>> clauses,
                            std::vector<std::string> synonyms);
  static bool IsWildcard(std::vector<std::unique_ptr<Clause>> &clauses);
  static bool SynonymCheck(QueryPtr &query);
 private:
  std::vector<std::unique_ptr<Clause>> clauses_;
  std::vector<std::string> synonyms_;
};
}  // namespace qps
