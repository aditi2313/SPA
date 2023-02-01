#include <iostream>
#include <vector>
#include "Table.h"
#include "Modifies.h"

using namespace std;

#ifndef SPA_MODIFIESTABLE_H
#define SPA_MODIFIESTABLE_H

namespace pkb {
    class ModifiesTable: public Table<Modifies>{

    };

#endif //SPA_MODIFIESTABLE_H
}