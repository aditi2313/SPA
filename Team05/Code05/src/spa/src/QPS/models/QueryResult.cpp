#include "QueryResult.h"

namespace qps {
void QueryResult::Intersect(QueryResult other_result) {
  std::set<models::EntityStub> result_list;

  auto it1 = query_results_.begin();
  auto it2 = other_result.query_results_.begin();

  for (; it1 != query_results_.end();) {
    if (it2 == other_result.query_results_.end()) break;
    if (*it1 == *it2) {
      result_list.insert(*it1);
    } else if (*it1 < *it2) {
      it1++;
    } else {
      it2++;
    }
  }

  query_results_ = result_list;
}
}
