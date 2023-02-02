#include "Formatter.h"

namespace qps {
// Takes in a QueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::vector<std::string> Formatter::FormatQuery(models::QueryResult query_result) {
  std::vector<std::string> output;
  EntSet& result_entities =
      query_result.get_query_results();
  for (const EntPtr& entity : result_entities) {
    output.push_back(std::move(*entity));
  }
  return output;
}
}  // namespace qps
