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

    inline pkb::IndexableTablePtr<T>
            FilterTable(pkb::IndexableTablePtr<T> table) override {
        pkb::IndexableTablePtr<T> result =
                std::make_unique<pkb::IndexableTable<T>>();
        auto indexes = table->get_indexes();
        if (indexes.find(line_) == indexes.end()) {
            return result;
        }
        auto row = table->get_row(line_);
        result->add_row(row->get_line(), row);
        return result;
    }

 private:
    int line_;
};
}  // namespace filter
