#include "QueryResult.h"

namespace qps {
// Given another list of query results (that are sorted
// in ascending order), override the list of this QueryResult
// object with the intersection between the two lists.
// Intersection is defined as the list of elements that occur
// in both lists.
void QueryResult::IntersectWith(QueryResultPtr &other_result) {
  EntityPtrList result_list;

  // Vector, hence not guaranteed to be in ascending order
  // Need to sort first
  this->Sort();
  other_result->Sort();

  auto it1 = query_results_.begin();
  auto it2 = other_result->query_results_.begin();

  while (
      it1 != query_results_.end()
          && it2 != other_result->query_results_.end()
      ) {
    // Need to dereference twice because it is
    // a vector of unique pointers
    if (*(*it1) == *(*it2)) {
      result_list.push_back((*it2)->Copy());
      it1++;
      it2++;
    } else if (*(*it1) < *(*it2)) {
      it1++;
    } else {
      // it2 > it1
      it2++;
    }
  }

  query_results_.clear();
  for (auto &entity : result_list) {
    query_results_.push_back(std::move(entity));
  }
}
}  // namespace qps
