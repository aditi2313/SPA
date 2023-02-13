#include "PredicateFilter.h"

namespace filter {

template<class T>
pkb::IndexableTablePtr<T> PredicateFilter<T>::FilterTable(pkb::IndexableTablePtr<T> table) {
    pkb::IndexableTablePtr<T> result =
            std::make_unique<pkb::IndexableTable<T>>();

    for (int line : table->get_indexes()) {
        auto data = table->get_row(line);
        if (predicate_(data)) {
            result->add_row(line, data);
        }
    }
    return std::move(result);
}
}  // namespace filter
