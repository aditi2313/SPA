#pragma once

#include "PKBWriter.h"
#include "models/CFG/ProgramCFG.h"

namespace sp {
class CFGExtractor : public PKBWriter {
 public:
  CFGExtractor(std::unique_ptr<pkb::PKBWrite> pkb_ptr)
      : PKBWriter(std::move(pkb_ptr)) {}

  void WriteCFG(cfg::ProgramCFG& program_cfg) {
    auto& procedure_map = program_cfg.get_procedure_cfg_map();
    for (auto& [_, cfg] : procedure_map) {
      WriteNext(cfg.get_root());
    }
  }

  void WriteNext(cfg::CFGNode& node) {
    if (node.is_empty() && !node.HasFirstChild() && !node.HasSecondChild()) {
      return;
    }
    if (node.is_empty()) {
      WriteNext(node.GetFirstChild());
    }
    auto& lines = node.get_lines();
    for (int i = 0, j = 1; j < lines.size(); ++j, ++i) {
      pkb_ptr_->AddNextData(lines[i], lines[j]);
    }
    int last_line = lines[lines.size() - 1];
    // add the next children
    if (node.HasFirstChild()) {
      WriteToNext(&(node.GetFirstChild()), last_line);
    }
    if (node.HasSecondChild()) {
      WriteToNext(&(node.GetSecondChild()), last_line);
    }
  }

 private:
  void WriteToNext(cfg::CFGNode* node, int last_line) {
    cfg::CFGNode* curr = node;
    while (curr->is_empty()) {
      curr = &(curr->GetFirstChild());
    }
    pkb_ptr_->AddNextData(last_line, curr->get_lines().at(0));
    WriteNext(*curr);
  }
};
}  // namespace sp
