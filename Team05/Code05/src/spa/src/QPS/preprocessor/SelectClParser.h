#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "../models/Query.h"
#include "../models/Clause.h"
#include "ParseState.h"
#include "QPS/models/Entity.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class SelectClParser {
 public:
  SelectClParser() {
    int num_states = 5;
    // Have to initialize them here as using the
    // {} constructor for unique pointers does not work.
    // State Order is defined as
    // Declaration -> Select -> (Such-That | Pattern | With)*
    states_.emplace_back(std::make_unique<DeclarationParseState>());
    states_.emplace_back(std::make_unique<SelectParseState>());
    states_.emplace_back(std::make_unique<SuchThatParseState>());
    states_.emplace_back(std::make_unique<PatternParseState>());
    states_.emplace_back(std::make_unique<WithParseState>());

    transition_table_.assign(num_states, std::vector<int>());

    transition_table_[0] = {1};  // Declare -> Select
    transition_table_[1] = {2, 3, 4};  // Select -> (Such-that | Pattern | With)
    transition_table_[2] = {3, 4};  // Such-that -> (Pattern | With)
    transition_table_[3] = {2, 4};  // Pattern -> (Such-that | With)
    transition_table_[4] = {2, 3};  // With -> (Such-that | Pattern)
  }

  std::vector<std::string> PreprocessQueryString(std::string query_string);
  std::unique_ptr<Query> ParseQuery(std::string query_string);

 private:
  int NextState(int current_state_index, std::string token);
  std::vector<std::unique_ptr<ParseState>> states_{};
  std::vector<std::vector<int>> transition_table_;
};
}  // namespace qps
