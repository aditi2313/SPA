#include "Formatter.h"

#include <utility>

#include "QPS/models/Entity.h"

namespace qps {
// Takes in a QueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::list<std::string> Formatter::FormatQuery(QueryResultPtr &query_result) {
  std::list<std::string> output;
  std::vector<Entity> result_entities = query_result->Sort();
  for (Entity entity : result_entities) {
    output.push_back(entity.to_str());
  }
  return output;
}
}  // namespace qps
