#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "data/AssignData.h"
#include "data/FollowData.h"
#include "data/ModifiesData.h"
#include "data/ParentData.h"
#include "data/UsesData.h"
#include "models/AST/factor_node/FactorNode.h"
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
  IndexableTable<FollowData> follow_table_;
  IndexableTable<ParentData> parent_table_;
  IndexableTable<UsesData> uses_table_;

  // ptr needed as Assign data contains a unique ptr
  // Without the use of a pointer
  // An alternative would be to overload the assign operator for AssignData.
  //
  // With the use of unique ptr, Indexable Table does not support such
  // behaviour, as we would have to move data every time we add a row. Therefore
  // shared ptr is used.
  IndexableTable<std::shared_ptr<AssignData>> assign_table_;

  void add_modifies_data(const int line,
                         const std::vector<std::string>& variables) {
    modifies_table_.add_row(line, ModifiesData(line, variables));
  }

  void add_assign_data(std::string variable, int line,
                       std::unique_ptr<ast::ExprNode> expression) {
    assign_table_.add_row(line, std::make_shared<AssignData>(
                                    variable, line, std::move(expression)));
  }
};

}  // namespace pkb
