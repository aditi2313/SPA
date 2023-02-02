#pragma once
#include <iostream>
#include <vector>

#include "PKB/data/ModifiesData.h"
#include "Table.h"

namespace pkb {
class ModifiesTable : public Table<ModifiesData> {};
}  // namespace pkb
