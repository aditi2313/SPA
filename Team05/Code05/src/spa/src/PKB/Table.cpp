#include "Table.h"

namespace pkb {

    template<class T>
    void Table<T>::add_row(T row) {
        rows.push_back(row);
    }

    template<class T>
    T Table<T>::get_row(int num) {
        return rows[num];
    }

}  // namespace pkb
