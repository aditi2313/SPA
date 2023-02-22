#pragma once

#include <string>
#include <unordered_map>

#include "CFG.h"

namespace cfg {
class ProgramCFG {
 public:
  ProgramCFG() {}
  
  /// <summary>
  /// Gets the cfg corresponding to the give procedure.
  /// </summary>
  /// <param name="proc">The procedure to add.</param>
  /// <returns></returns>
  CFG& get_cfg(std::string proc) { return procedure_to_cfg_map_.at(proc); }

  /// <summary>
  /// Adds the given procedure to the program cfg.
  /// </summary>
  /// <param name="proc">The procedure name to add.</param>
  /// <returns></returns>
  CFG& add_procedure(std::string proc) {
    procedure_to_cfg_map_[proc] = CFG();
    return procedure_to_cfg_map_[proc];
  }

 private:
  std::unordered_map<std::string, CFG> procedure_to_cfg_map_;
};
}  // namespace cfg
