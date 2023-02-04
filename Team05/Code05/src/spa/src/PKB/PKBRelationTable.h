#pragma once
#include <string>
#include <vector>

#include "data/ModifiesData.h"
#include "tables/IndexableTable.h"

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
  IndexableTable<ModifiesData> modifies_table_;

  void add_modifies_data(const int line,
                         const std::vector<std::string>& variables) {
    modifies_table_.add_row(line, ModifiesData(line, variables));
  }
};

}  // namespace pkb
