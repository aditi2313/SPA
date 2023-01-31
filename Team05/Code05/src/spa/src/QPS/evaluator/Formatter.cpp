#include "Formatter.h"

namespace qps {
// Takes in a QueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::vector<std::string> Formatter::FormatQuery(QueryResult query_result) {
  std::vector<std::string> output;
  std::vector<models::EntityStub> result_entities = query_result.GetQueryResults();
  for (models::EntityStub entity : result_entities) {
    output.push_back(entity);
  }
  return output;
}
}
