#pragma once
#include <iostream>
#include <vector>
#include "Table.h"
#include "Modifies.h"

namespace pkb {
class ModifiesTable: public Table<Modifies>{};
}  // namespace pkb
