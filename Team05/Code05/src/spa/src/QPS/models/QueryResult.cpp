#include "QueryResult.h"

namespace qps {
// Given another list of query results (that are sorted
// in ascending order), override the list of this QueryResult
// object with the intersection between the two lists.
// Intersection is defined as the list of elements that occur
// in both lists.
void QueryResult::IntersectWith(QueryResult other_result) {
  std::set<models::Entity> result_list;

  auto it1 = query_results_.begin();
  auto it2 = other_result.query_results_.begin();

  for (; it1 != query_results_.end();) {
    if (it2 == other_result.query_results_.end()) break;
    if (*it1 == *it2) {
      result_list.insert(*it1);
    } else if (*it1 < *it2) {
      it1++;
    } else {
      // *it2 > *it1
      it2++;
    }
  }

  query_results_ = result_list;
}
}  // namespace qps
