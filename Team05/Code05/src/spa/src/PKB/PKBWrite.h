#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "PKBRelationTable.h"
#include "data/ModifiesData.h"

namespace pkb {
class PKBWrite {
 public:
  explicit PKBWrite(
      std::unique_ptr<PKBRelationTable> other_pkb_relation_table) {
    this->pkb_relation_table = std::move(other_pkb_relation_table);
  }

  /// <summary>
  /// Adds a modifies row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="variables"></param>
  void AddModifiesData(int line, const std::vector<std::string>& variables);
  // Todo(Gab): add datastructure for assignment as well as tables.

  void AddAssign(int id) = delete;
  /// <summary>
  /// Ends the writing.
  /// Renders this writer useless.
  ///
  /// </summary>
  /// <returns>The unique pointer for PKB Relation Table</returns>
  inline std::unique_ptr<PKBRelationTable> EndWrite() {
    return std::move(pkb_relation_table);
  }

 private:
  std::unique_ptr<PKBRelationTable> pkb_relation_table;
};
}  // namespace pkb
