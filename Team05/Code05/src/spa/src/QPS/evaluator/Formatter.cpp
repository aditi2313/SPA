#include "Formatter.h"

#include <set>
#include <utility>

#include "models/Entity.h"

namespace qps {
// Takes in a QueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::list<std::string> Formatter::FormatQuery(QueryResultPtr &query_result) {
  std::list<std::string> output;
  EntityPtrList &result_entities =
      query_result->get_query_results();
  for (const EntityPtr &entity : result_entities) {
    output.push_back(entity->operator std::string());
  }
  return output;
}
}  // namespace qps
