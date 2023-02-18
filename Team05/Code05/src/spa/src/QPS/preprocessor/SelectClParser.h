#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "../models/Query.h"
#include "../models/Clause.h"
#include "ParseState.h"
#include "models/Entity.h"
#include "models/Stmt.h"
#include "common/Exceptions.h"

namespace qps {
class SelectClParser {
 public:
  SelectClParser() {
    int num_states = 4;
    // Have to initialize them here as using the
    // {} constructor for unique pointers does not work.
    // State Order is defined as
    // Declaration -> Synonym -> Such-That -> Pattern
    states_.emplace_back(std::make_unique<DeclarationParseState>());
    states_.emplace_back(std::make_unique<SelectParseState>());
    states_.emplace_back(std::make_unique<SuchThatParseState>());
    states_.emplace_back(std::make_unique<PatternParseState>());

    transition_table_.assign(num_states, std::vector<int>());
    for (int i = 0; i < num_states - 1; ++i) {
      transition_table_[i].push_back(i + 1);
    }
    // Can go to Pattern without passing through Such-That
    transition_table_[1].push_back(3);
  }

  std::vector<std::string> PreprocessQueryString(std::string query_string);
  std::unique_ptr<Query> ParseQuery(std::string query_string);

 private:
  int NextState(int current_state_index, std::string token);
  std::vector<std::unique_ptr<ParseState>> states_{};
  std::vector<std::vector<int>> transition_table_;
};
}  // namespace qps
