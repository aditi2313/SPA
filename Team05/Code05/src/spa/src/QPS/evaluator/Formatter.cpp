#include "Formatter.h"

#include <set>
#include <utility>

#include "models/EntityStub.h"

namespace qps {
// Takes in a QueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::list<std::string> Formatter::FormatQuery(QueryResult query_result) {
  std::list<std::string> output;
  std::set<models::EntityStub> &result_entities =
      query_result.get_query_results();
  for (const models::EntityStub &entity : result_entities) {
    output.push_back(entity);
  }
  return output;
}
}  // namespace qps
