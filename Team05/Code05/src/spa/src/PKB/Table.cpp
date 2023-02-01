#include "Table.h"

using namespace std;

namespace pkb {

    template<class T>
    void Table<T>::addRow(T row) {
        rows.push_back(row);
    }

    template<class T>
    T Table<T>::getRow(int num) {
        return rows[num];
    }

}  // namespace pkb

