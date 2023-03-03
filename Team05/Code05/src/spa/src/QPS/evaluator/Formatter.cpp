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
    auto result_entities = list_query_result->get_query_results();
    if(result_entities.empty()) return {};

    int num_columns = result_entities.size();
    int num_queries = result_entities.at(0).size();
    for (int i = 0; i < num_queries; ++i) {
      std::string result = "";
      for(int j = 0; j < num_columns; ++j) {
        if(j > 0) {
          result += ", ";
        }
        result +=
            result_entities.at(j).at(i).to_str();
      }
      output.push_back(result);
    }
  }

  return output;
}
}  // namespace qps
