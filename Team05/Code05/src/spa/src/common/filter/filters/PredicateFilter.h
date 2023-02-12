#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"
#include "PKB/tables/IndexableTable.h"
#include "common/Exceptions.h"

namespace filter {

template<class T, typename Predicate>
class PredicateFilter
        : public IndexableFilter<T> {
 public:
    explicit PredicateFilter(Predicate predicate) : predicate_(predicate) {}

    pkb::IndexableTablePtr<T> FilterTable(pkb::IndexableTablePtr<T>) override;

 private:
    Predicate predicate_;
};
}  // namespace filter
