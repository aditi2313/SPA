#include "Formatter.h"

#include <utility>
#include <vector>

#include "QPS/models/Entity.h"

namespace qps {
// Takes in a QueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::list<std::string> Formatter::FormatQuery(QueryResultPtr &query_result) {
  std::list<std::string> output;

  if (query_result->is_boolean()) {
    BooleanQueryResult *boolean_query_result =
        dynamic_cast<BooleanQueryResult *>(query_result.get());
    output.emplace_back(boolean_query_result->is_true() ? "TRUE" : "FALSE");
  } else {
    ListQueryResult *list_query_result =
        dynamic_cast<ListQueryResult *>(query_result.get());
    std::vector<Entity> result_entities = list_query_result->Sort();
    for (Entity entity : result_entities) {
      output.push_back(entity.to_str());
    }
  }

  return output;
}
}  // namespace qps
