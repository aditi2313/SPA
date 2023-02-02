#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "../models/Query.h"
#include "ParseState.h"
#include "models/EntityStub.h"

namespace qps {
class Parser {
 public:
  Parser() {
    states_.emplace_back(std::make_unique<DeclarationParseState>());
    states_.emplace_back(std::make_unique<SynonymParseState>());
    states_.emplace_back(std::make_unique<SuchThatParseState>());
    states_.emplace_back(std::make_unique<PatternParseState>());
  }

  Query ParseQuery(std::string query_string);

  static bool is_design_entity(std::string identifier) {
    return design_entity_identifiers_.find(identifier) != design_entity_identifiers_.end();
  }

  static models::EntityStub get_design_entity(std::string identifier) {
    return design_entity_identifiers_.at(identifier);
  }

  static inline bool is_ident(std::string str) {
    if (str.empty() || !isalpha(str[0])) return false;
    for (char c : str) {
      if (!isalnum(c)) return false;
    }
    return true;
  }

 private:
  std::vector<std::unique_ptr<ParseState>> states_{};
  std::vector<int> arr{1};
  bool ShouldGoToNextState(int current_state_index, std::string token);
  std::string PreprocessQueryString(std::string query_string);

  static inline std::unordered_map<std::string, models::EntityStub> design_entity_identifiers_{
      {"stmt", models::EntityStub()},
      {"read", models::EntityStub()},
      {"print", models::EntityStub()},
      {"call", models::EntityStub()},
      {"while", models::EntityStub()},
      {"if", models::EntityStub()},
      {"assign", models::EntityStub()},
      {"variable", models::EntityStub()},
      {"constant", models::EntityStub()},
      {"procedure", models::EntityStub()},
  };

};
}  // namespace qps