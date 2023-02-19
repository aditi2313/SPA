#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "PKBRelationTable.h"
#include "data/ModifiesData.h"
#include "models/AST/factor_node/FactorNode.h"

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
  void AddModifiesData(int line,
                       const std::unordered_set<std::string>& variables);

  /// <summary>
  /// Adds assign data.
  /// </summary>
  /// <param name="line">The line of the assignment</param>
  /// <param name="expression">The unique pointer to the expression on the
  /// rhs</param>
  void AddAssignData(std::string variable, int line,
                     std::unique_ptr<ast::ExprNode> expression);

  /// <summary>
  /// Adds a uses row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="variable_names"></param>
  void AddUsesData(int line,
                   const std::unordered_set<std::string>& variable_names);

  /// <summary>
  /// Adds a follows row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="follows"></param>
  void AddFollowsData(int line, const int follows);

  /// <summary>
  /// Adds a parent row.
  ///
  /// </summary>
  /// <param name="line"></param>
  /// <param name="parent_line"></param>
  void AddParentData(int line, const int parent_line);

  void add_variable(std::string variable) {
    pkb_relation_table_->variables_.insert(variable);
  }

  void add_constant(int constant) {
    pkb_relation_table_->constants_.insert(constant);
  }

  void add_stmt(int stmt) { pkb_relation_table_->stmts_.insert(stmt); }

  void add_while(int w) { pkb_relation_table_->whiles_.insert(w); }

  void add_assign(int a) { pkb_relation_table_->assign_.insert(a); }

  void add_call(int c) { pkb_relation_table_->calls_.insert(c); }

  void add_procedure(std::string p) {
    pkb_relation_table_->procedures_.insert(p);
  }

  void add_print(int p) { pkb_relation_table_->print_.insert(p); }

  void add_read(int r) { pkb_relation_table_->read_.insert(r); }

  void add_if(int i) { pkb_relation_table_->if_.insert(i); }

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
    ProcessFollows();
    ProcessParent();
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

  void ProcessUses();
  void RecursiveProcessUses(int);
  std::unique_ptr<PKBRelationTable> pkb_relation_table_;
};
}  // namespace pkb
