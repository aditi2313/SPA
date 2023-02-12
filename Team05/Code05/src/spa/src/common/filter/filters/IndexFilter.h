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

template<class T>
class IndexFilter
        : public IndexableFilter<T> {
 public:
    explicit IndexFilter(int line) : line_(line) {}

    pkb::IndexableTablePtr<T> FilterTable(pkb::IndexableTablePtr<T>) override;

 private:
    int line_;
};
}
