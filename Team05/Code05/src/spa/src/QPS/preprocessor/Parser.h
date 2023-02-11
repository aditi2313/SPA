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
class Parser {
 public:
  Parser() {
    // Have to initialize them here as using the
    // {} constructor for unique pointers does not work.
    // State Order is defined as
    // Declaration -> Synonym -> Such-That -> Pattern
    states_.emplace_back(std::make_unique<DeclarationParseState>());
    states_.emplace_back(std::make_unique<SynonymParseState>());
    states_.emplace_back(std::make_unique<SuchThatParseState>());
    states_.emplace_back(std::make_unique<PatternParseState>());
  }

  std::vector<std::string> PreprocessQueryString(std::string query_string);
  bool ShouldGoToNextState(int current_state_index, std::string token);
  std::unique_ptr<Query> ParseQuery(std::string query_string);

 private:
  std::vector<std::unique_ptr<ParseState>> states_{};
};
}  // namespace qps
