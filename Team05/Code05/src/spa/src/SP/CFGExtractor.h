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
    if (node.is_empty() && !node.HasFirstChild() && !node.HasSecondChild()) {
      return;
    }
    if (node.is_empty()) {
      WriteNext(cfg.GetFirstChild(node), cfg);
      return;
    }
    auto& lines = node.get_lines();
    // TODO(Gab): Consider using id to remember visited instead
    int last_line = lines[lines.size() - 1];
    if (visited.count(last_line)) {
      return;
    }
    for (int i = 0, j = 1; j < lines.size(); ++j, ++i) {
      pkb_ptr_->AddNextData(lines[i], lines[j]);
    }

    visited.insert(last_line);
    // add the next children
    if (node.HasFirstChild()) {
      WriteToNext(cfg.GetFirstChild(node), cfg, last_line);
    }
    if (node.HasSecondChild()) {
      WriteToNext(cfg.GetFirstChild(node), cfg, last_line);
    }
  }

 private:
  std::unordered_set<int> visited;
  void WriteToNext(cfg::CFGNode& node, cfg::CFG& cfg, int last_line) {
    cfg::CFGNode* curr = &node;
    while (curr->is_empty()) {
      curr = &cfg.GetFirstChild(*curr);
    }
    pkb_ptr_->AddNextData(last_line, curr->get_lines().at(0));
    WriteNext(*curr, cfg);
  }
};
}  // namespace sp
