#include "IndexFilter.h"

namespace filter {

template<class T>
pkb::IndexableTablePtr<T> IndexFilter<T>::FilterTable
(pkb::IndexableTablePtr<T> table) {
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
}  // namespace filter
