#include "Formatter.h"

#include <utility>
#include <vector>

#include "QPS/models/Entity.h"

namespace qps {
// Takes in a BooleanQueryResult and returns a list of string
// that is "TRUE" or "FALSE" depending on the result.
std::list<std::string> Formatter::FormatBooleanQuery(bool result) {
  std::list<std::string> output;
  output.emplace_back(result ? "TRUE" : "FALSE");

  return output;
}

// Takes in a ListQueryResult and returns an array of string
// in the specified format, with no duplicates.
// If there are no answers to the query, the array is empty.
std::list<std::string> Formatter::FormatListQuery(
    std::vector<std::vector<Entity>> &results) {
  std::list<std::string> output;
  if (results.empty()) return {};

  int num_rows = results.size();
  int num_columns = results.at(0).size();
  for (int i = 0; i < num_rows; ++i) {
    std::string row = "";
    for (int j = 0; j < num_columns; ++j) {
      if (j > 0) {
        row += " ";
      }
      row +=
          results.at(i).at(j).to_str();
    }
    output.push_back(row);
  }
  return output;
}
}  // namespace qps
