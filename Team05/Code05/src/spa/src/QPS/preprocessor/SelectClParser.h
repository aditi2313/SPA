#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "QPS/models/Query.h"
#include "QPS/models/clauses/Clause.h"
#include "parse_states/Export.h"
#include "QPS/models/Entity.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class SelectClParser {
 public:
  SelectClParser() {
    // Initialize constants
    int num_states = 5;

    int kDeclarationIndex = 0;
    int kSelectIndex = 1;
    int kSuchThatIndex = 2;
    int kPatternIndex = 3;
    int kWithIndex = 4;


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

    transition_table_[kDeclarationIndex] =
        {kDeclarationIndex, kSelectIndex};

    transition_table_[kSelectIndex] =
        {kSuchThatIndex, kPatternIndex, kWithIndex};

    transition_table_[kSuchThatIndex] =
        {kSuchThatIndex, kPatternIndex, kWithIndex};

    transition_table_[kPatternIndex] =
        {kPatternIndex, kSuchThatIndex, kWithIndex};

    transition_table_[kWithIndex] =
        {kWithIndex, kSuchThatIndex, kPatternIndex};
  }

  std::vector<std::string> PreprocessQueryString(std::string query_string);
  std::unique_ptr<Query> ParseQuery(std::string query_string);

 private:
  int NextState(int current_state_index, std::string token);
  std::vector<std::unique_ptr<ParseState>> states_{};
  std::vector<std::vector<int>> transition_table_;

  // Special characters are characters that PreprocessQueryString
  // will insert spaces around to ensure correct delimitation
  // ; ( ) , < > = _
  std::unordered_set<std::string> special_characters_{
      PQL::kSemicolonToken,
      PQL::kOpenBktToken,
      PQL::kCloseBktToken,
      PQL::kCommaToken,
      PQL::kTupleOpenBktToken,
      PQL::kTupleCloseBktToken,
      PQL::kEqualToken,
      PQL::kUnderscoreToken,
  };
};
}  // namespace qps
