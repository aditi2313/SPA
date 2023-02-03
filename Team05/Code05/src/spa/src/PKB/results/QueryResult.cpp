#include "QueryResult.h"

#include <memory>
#include <unordered_set>

#include "PKB/tables/IndexableTable.h"

namespace pkb {
// TODO: switch for a faster soln
template <class T>
std::unique_ptr<QueryResult<T>> QueryResult<T>::IntersectWith(
    std::unique_ptr<QueryResult<T>> other_q_result) {
  auto o_result = other_q_result->result_;
}

}  // namespace pkb
