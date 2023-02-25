#include "QueryResult.h"

namespace qps {
// Given another list of query results (that are sorted
// in ascending order), override the list of this QueryResult
// object with the intersection between the two lists.
// Intersection is defined as the list of elements that occur
// in both lists.
void QueryResult::IntersectWith(QueryResult &other_result) {
  EntitySet result_list;

  auto arr1 = this->Sort();
  auto arr2 = other_result.Sort();

  auto it1 = arr1.begin();
  auto it2 = arr2.begin();

  while (
      it1 != arr1.end()
          && it2 != arr2.end()
      ) {
    // Need to dereference twice because it is
    // a vector of unique pointers
    if (*it1 == *it2) {
      result_list.insert(*it2);
      it1++;
      it2++;
    } else if (*it1 < *it2) {
      it1++;
    } else {
      // it2 > it1
      it2++;
    }
  }

  query_results_ = result_list;
}
}  // namespace qps
