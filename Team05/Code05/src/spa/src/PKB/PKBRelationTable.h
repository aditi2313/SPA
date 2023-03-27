#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "data/Export.h"
#include "models/AST/factor_node/FactorNode.h"
#include "tables/DoubleIndexTable.h"
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
  IndexableTable<CallsData> calls_table_;
  CallsDTable calls_d_table_;
  ParentDTable parent_d_table_;
  FollowsDTable follows_d_table_;
  NextDTable next_d_table_;
  IndexableTable<NextData> next_table_;
  IndexableTable<ConditionData> condition_table_;

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
  std::unordered_map<int, std::string> line_to_var_name_;
  std::unordered_map<int, std::string> line_to_proc_name_;

  friend bool operator==(const PKBRelationTable& LHS,
                         const PKBRelationTable& RHS) {
    return LHS.modifies_table_ == RHS.modifies_table_ &&
           LHS.follows_table_ == RHS.follows_table_ &&
           LHS.parent_table_ == RHS.parent_table_ &&
           LHS.uses_table_ == RHS.uses_table_ &&
           LHS.assign_table_ == RHS.assign_table_ &&
           LHS.calls_table_ == RHS.calls_table_ &&
           LHS.next_table_ == RHS.next_table_ &&
           LHS.constants_ == RHS.constants_ && LHS.whiles_ == RHS.whiles_ &&
           LHS.stmts_ == RHS.stmts_ && LHS.calls_ == RHS.calls_ &&
           LHS.assign_ == RHS.assign_ && LHS.read_ == RHS.read_ &&
           LHS.print_ == RHS.print_ && LHS.if_ == RHS.if_ &&
           LHS.variables_ == RHS.variables_ &&
           LHS.procedures_ == RHS.procedures_;
  }

  void add_modifies_data(const std::variant<int, std::string> line,
                         const std::unordered_set<std::string>& variables) {
    if (modifies_table_.exists(line)) {
      auto& data = modifies_table_.get_row(line);
      data.add_variables(variables);
      return;
    }
    modifies_table_.add_row(line, ModifiesData(line, variables));
  }

  void add_assign_data(const std::string variable, const int line,
                       std::unique_ptr<ast::ExprNode> expression) {
    variables_.insert(variable);
    assign_table_.add_row(line,
                          AssignData(variable, line, std::move(expression)));
  }

  void add_uses_data(const std::variant<int, std::string> line,
                     const std::unordered_set<std::string>& variable_names) {
    if (uses_table_.exists(line)) {
      auto& data = uses_table_.get_row(line);
      data.add_variables(variable_names);
      return;
    }
    uses_table_.add_row(line, UsesData(line, variable_names));
  }

  void add_follows_data(const int line, const int follows) {
    FollowsData f(line, follows);
    follows_d_table_.add_row(line, follows, f);
  }

  void add_parent_data(const int line, const int child_line) {
    ParentData p(line);
    parent_d_table_.add_row(line, child_line, p);
    auto& data = parent_d_table_.get_row(line);
    data.add_direct_child(child_line);
  }

  void add_calls_data(const std::string& caller, const std::string& callee) {
    CallsData c(caller);
    calls_d_table_.add_row(caller, callee, c);
    auto& data = calls_d_table_.get_row(caller);
    data.add_to_direct_calls(callee);
  }

  void add_next_data(const int line, const int next) {
    NextData n(line);
    next_d_table_.add_row(line, next, n);
    auto& data = next_d_table_.get_row(line);
    data.add_to_next_im_list(next);
  }

  void add_condition_data(
      const std::variant<int, std::string> line,
      const std::unordered_set<std::string>& variable_names) {
    condition_table_.add_row(line, ConditionData(line, variable_names));
  }
};
}  // namespace pkb
