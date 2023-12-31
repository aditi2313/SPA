#pragma once

#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>

#include "CFG.h"

namespace cfg {
class ProgramCFG {
 public:
  ProgramCFG() {}

  /// <summary>
  /// Adds the given procedure to the program cfg.
  /// </summary>
  /// <param name="proc">The procedure name to add.</param>
  /// <returns></returns>
  CFG& add_procedure(std::string proc) {
    procedure_to_cfg_map_.insert(std::make_pair(proc, CFG(this)));
    return procedure_to_cfg_map_.at(proc);
  }

  /// <summary>
  /// Gets the cfg corresponding to the give procedure.
  /// </summary>
  /// <param name="proc">The procedure to add.</param>
  /// <returns></returns>
  CFG& get_cfg(std::string proc) { return procedure_to_cfg_map_.at(proc); }

  /// <summary>
  /// Gets the cfg node that contains the given line number.
  /// </summary>
  /// <param name="line">The line number contained in the code block of the
  /// cfg node</param> <returns>The cfg node containing the line
  /// number</returns>
  CFGNode& get_node(int line) { return *(line_to_cfg_map_[line]); }

  friend bool operator==(const ProgramCFG& LHS, const ProgramCFG& RHS) {
    return LHS.procedure_to_cfg_map_ == RHS.procedure_to_cfg_map_;
  }

  std::unordered_map<std::string, CFG>& get_procedure_cfg_map() {
    return procedure_to_cfg_map_;
  }

 private:
  // mapping to procedure.
  std::unordered_map<std::string, CFG> procedure_to_cfg_map_;

  // unordered map mapping line number to cfg node.
  std::unordered_map<int, CFGNode*> line_to_cfg_map_;
  CFGNodeId id_ctr_ = 0;

  void AddLineToCfg(int line, CFGNode* node) {
    assert(line_to_cfg_map_.find(line) == line_to_cfg_map_.end());
    line_to_cfg_map_[line] = node;
  }
  CFGNodeId GetAndIncrementId() { return id_ctr_++; }
  friend class CFG;
};
}  // namespace cfg
