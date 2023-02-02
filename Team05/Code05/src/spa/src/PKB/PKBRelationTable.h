#pragma once
#include <string>
#include <vector>

#include "data/ModifiesData.h"
#include "tables/ModifiesTable.h"

namespace pkb {
/// <summary>
/// The table of relations
/// used to wrap around all the
/// tables used in the pkb.
/// </summary>
class PKBRelationTable {
 private:
  friend class PKBWrite;
  friend class PKBRead;
  ModifiesTable modifies_table_;

  void add_modifies(const int line, const std::vector<std::string>& variables) {
    modifies_table_.add_row(line, ModifiesData(line, variables));
  }

  const ModifiesTable& get_modifies() { return modifies_table_; }
};

}  // namespace pkb
