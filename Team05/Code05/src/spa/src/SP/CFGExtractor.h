#pragma once

#include <memory>
#include <unordered_set>
#include <utility>

#include "PKBWriter.h"
#include "models/CFG/ProgramCFG.h"

namespace sp {
class CFGExtractor : public PKBWriter {
 public:
  explicit CFGExtractor(std::unique_ptr<pkb::PKBWrite> pkb_ptr)
      : PKBWriter(std::move(pkb_ptr)) {}

  void WriteCFG(cfg::ProgramCFG& program_cfg) {
    auto& procedure_map = program_cfg.get_procedure_cfg_map();
    for (auto& [_, cfg] : procedure_map) {
      WriteNext(cfg.get_root(), cfg);
    }
  }

  void WriteNext(cfg::CFGNode& node, cfg::CFG& cfg) {
    if (node.is_empty()) {
      if (node.HasFirstChild()) WriteNext(cfg.GetFirstChild(node), cfg);
      return;
    }
    // TODO(Gab): Consider using id to remember visited instead
    int last_line = *(node.back());
    if (visited.count(last_line)) {
      return;
    }
    for (auto start = node.front(); !start.IsMax(); start++) {
      pkb_ptr_->AddNextData(*start, *(start + 1));
    }

    visited.insert(last_line);
    // add the next children
    if (node.HasFirstChild()) {
      WriteToNext(cfg.GetFirstChild(node), cfg, last_line);
    }
    if (node.HasSecondChild()) {
      WriteToNext(cfg.GetSecondChild(node), cfg, last_line);
    }
  }

 private:
  std::unordered_set<int> visited;
  void WriteToNext(cfg::CFGNode& node, cfg::CFG& cfg, int last_line) {
    cfg::CFGNode* curr = &node;
    while (curr->is_empty()) {
      if (!curr->HasFirstChild()) return;
      curr = &cfg.GetFirstChild(*curr);
    }
    pkb_ptr_->AddNextData(last_line, *(curr->front()));
    WriteNext(*curr, cfg);
  }
};
}  // namespace sp
