#pragma once

#include <functional>
#include <memory>
#include <utility>

#include "PKB/tables/IndexableTable.h"

namespace pkb {

template <class T>
class QueryResult {
 public:
  QueryResult(std::unique_ptr<IndexableTable<T>> result) {
    result_ = std::move(result);
  }
  std::unique_ptr<IndexableTable<T>> get_result() {
    result_retrieved = true;
    return std::move(result);
  }
  std::unique_ptr<QueryResult<T>> IntersectWith(
      std::unique_ptr<QueryResult<T>> result);

 private:
  // indicates if the result has been retrieved
  bool result_retrieved_ = false;
  std::unique_ptr<IndexableTable<T>> result_;
};

template <class T>
using QueryResultPtr = std::unique_ptr<QueryResult<T>>;
}  // namespace pkb