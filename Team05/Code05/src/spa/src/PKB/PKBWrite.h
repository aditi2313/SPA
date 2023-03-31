#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKBRelationTable.h"
#include "data/ModifiesData.h"
#include "common/logging/Logger.h"
#include "models/AST/factor_node/FactorNode.h"

// optimisations snuff
namespace pkb {
class PKBWrite {
 public:
  explicit PKBWrite(
      std::unique_ptr<PKBRelationTable> other_pkb_relation_table) {
    this->pkb_relation_table_ = std::move(other_pkb_relation_table);
  }

  /// <summary>
  /// Adds a modifies row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="variables"></param>
  void AddModifiesData(Key line,
                       const VarSet& variables);

  /// <summary>
  /// Adds assign data.
  /// </summary>
  /// <param name="line">The line of the assignment</param>
  /// <param name="expression">The unique pointer to the expression on the
  /// rhs</param>
  void AddAssignData(std::string variable, Line line,
                     std::unique_ptr<ast::ExprNode> expression);

  /// <summary>
  /// Adds a uses row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="variable_names"></param>
  void AddUsesData(const Key line,
                   const VarSet& variable_names);

  /// <summary>
  /// Adds a follows row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="follows"></param>
  void AddFollowsData(Line line, const Line follows);

  /// <summary>
  /// Adds a parent row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="parent_line"></param>
  void AddParentData(Line line, const Line parent_line);

  /// <summary>
  /// Adds a calls row.
  ///
  /// </summary>
  /// <param name="caller"></param>
  /// <param name="callee"></param>
  void AddCallsData(Proc caller, Proc callee);

  /// <summary>
  /// Adds a next row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="next"></param>
  void AddNextData(Line line, const Line next);

  /// <summary>
  /// Adds a conditions row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="variable_names"></param>
  void AddConditionData(const Key line,
                   const VarSet& variable_names);

  void add_variable(Var variable) {
    pkb_relation_table_->variables_.insert(variable);
  }

  void add_constant(Line constant) {
    pkb_relation_table_->constants_.insert(constant);
  }

  void add_stmt(Line stmt) {
      pkb_relation_table_->stmts_.insert(stmt);
  }

  void add_while(Line w) {
      pkb_relation_table_->whiles_.insert(w);
  }

  void add_assign(Line a) {
      pkb_relation_table_->assign_.insert(a);
  }

  void add_call(Line c) {
      pkb_relation_table_->calls_.insert(c);
  }

  void add_procedure(Proc p) {
      pkb_relation_table_->procedures_.insert(p);
  }

  void add_print(Line p) {
      pkb_relation_table_->print_.insert(p);
  }

  void add_read(Line r) {
      pkb_relation_table_->read_.insert(r);
  }

  void add_if(Line i) {
      pkb_relation_table_->if_.insert(i);
  }

  void set_var_name_for_line(Line line, Var var_name) {
      pkb_relation_table_->line_to_var_name_[line] = var_name;
  }

  void set_proc_name_for_line(Line line, Proc proc_name) {
      pkb_relation_table_->line_to_proc_name_[line] = proc_name;
  }


  /// <summary>
  /// Ends the writing.
  /// Renders this writer useless.
  ///
  /// </summary>
  /// <returns>The unique pointer for PKB Relation Table</returns>
  inline std::unique_ptr<PKBRelationTable> EndWrite() {
    return std::move(pkb_relation_table_);
  }

  inline std::unique_ptr<PKBRelationTable> ProcessTableAndEndWrite() {
    logging::Logger::ResetClock();
    ProcessFollows();
    logging::Logger::LogAndStop("Processed follows");
    ProcessParent();
    logging::Logger::LogAndStop("Processed parent");
    ProcessCalls();
    logging::Logger::LogAndStop("Processed calls");
    return std::move(pkb_relation_table_);
  }

 private:
  /// <summary>
  /// Processes the
  /// current follows table
  /// to obtain all the Follows* lines.
  /// </summary>
  void ProcessFollows();

  /// <summary>
  /// Processes the current
  /// parent table to obtain all the Parent* lines.
  /// </summary>
  void ProcessParent();

  /// <summary>
  /// Processes the current
  /// calls table to obtain all the Calls* lines.
  /// </summary>
  void ProcessCalls();

  std::unique_ptr<PKBRelationTable> pkb_relation_table_;
};
}  // namespace pkb
