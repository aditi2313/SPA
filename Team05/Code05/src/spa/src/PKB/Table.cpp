#include "Table.h"

namespace pkb {

    template<class T>
    T Table<T>::get_row(int num) {
        return rows_.at(num);
    }

}  // namespace pkb
