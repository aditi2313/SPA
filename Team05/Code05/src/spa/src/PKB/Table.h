#include <iostream>
#include <vector>

using namespace std;

#ifndef SPA_TABLE_H
#define SPA_TABLE_H

namespace pkb {

    template <class T>
    class Table {
        public:
            vector<T> rows;
            void addRow(T row);
            T getRow(int num);
    };

#endif //SPA_TABLE_H
}

