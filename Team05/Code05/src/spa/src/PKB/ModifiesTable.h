#pragma once
#include <iostream>
#include <vector>
#include "Table.h"
#include "ModifiesData.h"

namespace pkb {
class ModifiesTable: public Table<ModifiesData>{};
}  // namespace pkb
