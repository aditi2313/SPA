#pragma once
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "data/AssignData.h"
#include "data/FollowsData.h"
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
///
/// TODO(Gab) Think of a better name for this construct.
/// </summary>
class PKBRelationTable {
 private:
  friend class PKBWrite;
  friend class PKBRead;
  IndexableTable<ModifiesData> modifies_table_;
  IndexableTable<FollowsData> follows_table_;
  IndexableTable<ParentData> parent_table_;
  IndexableTable<UsesData> uses_table_;
  IndexableTable<AssignData> assign_table_;
  std::unordered_set<int> constants_;
  std::unordered_set<int> whiles_;
  std::unordered_set<int> stmts_;
  std::unordered_set<int> calls_;
  std::unordered_set<int> assign_;
  std::unordered_set<int> read_;
  std::unordered_set<int> print_;
  std::unordered_set<int> if_;
  std::unordered_set<std::string> variables_;
  std::unordered_set<std::string> procedures_;

  void add_modifies_data(const int line,
                         const std::unordered_set<std::string>& variables) {
    modifies_table_.add_row(line, ModifiesData(line, variables));
  }

  void add_assign_data(std::string variable, int line,
                       std::unique_ptr<ast::ExprNode> expression) {
    variables_.insert(variable);
    assign_table_.add_row(line,
                          AssignData(variable, line, std::move(expression)));
  }

  void add_uses_data(const int line,
                         const std::unordered_set<std::string>&
                                 variable_names) {
      uses_table_.add_row(line, UsesData(line, variable_names));
  }

  void add_follows_data(const int line, const int follows) {
      follows_table_.add_row(line, FollowsData(line, follows));
  }

  void add_parent_data(const int line, const int parent_line) {
      parent_table_.add_row(line, ParentData(line, parent_line));
  }
};
}  // namespace pkb
