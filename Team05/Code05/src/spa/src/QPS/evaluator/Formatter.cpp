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

  if (query_result->IsBoolean()) {
    // Note: This is for ADVANCED SPA requirements
    BoolQueryResult *bool_query_result = dynamic_cast<BoolQueryResult *>(
        query_result.get());
    bool_query_result->IsTrue()
    ? output.push_back("TRUE")
    : output.push_back("FALSE");

  } else {
    ListQueryResult *list_query_result = dynamic_cast<ListQueryResult *>(
        query_result.get());
    list_query_result->Sort();
    EntityPtrList &result_entities =
        list_query_result->get_query_results();
    for (const EntityPtr &entity : result_entities) {
      output.push_back(entity->operator std::string());
    }
  }

  return output;
}
}  // namespace qps
