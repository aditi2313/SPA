#include <sstream>

#include "Parser.h"

namespace qps {

bool Parser::ShouldGoToNextState(int current_state_index, std::string token) {
  if (current_state_index >= states_.size() - 1) return false;  // last stage
  return token == states_.at(current_state_index + 1)->kTransitionKeyword;
}

// Inserts whitespaces around special characters
// (e.g. semicolons and brackets) for
// easier delimitation in ParseQuery
std::string PreprocessQueryString(std::string query_string) {
  std::string output = "";
  std::string special_characters = ";(),";
  for (char c : query_string) {
    if (special_characters.find(c) != std::string::npos) {
      output += ' ' + c + ' ';
    } else {
      output += c;
    }
  }
  return output;
}

Query Parser::ParseQuery(std::string query_string) {
  Query query;
  std::stringstream ss(PreprocessQueryString(query_string));
  std::vector<std::string> tokens;
  std::string token;
  while (ss >> token) {
    // Separates query string by whitespace.
    // Works for multiple whitespaces too.
    tokens.push_back(token);
  }

  int current_state_index = 0;
  auto itr = tokens.begin();
  while (itr != tokens.end()) {
    if (ShouldGoToNextState(current_state_index, *itr)) {
      continue;  // go to next state
    }
    itr = states_.at(current_state_index)->parse(tokens, itr, &query);
  }

  return query;
}
}  // namespace qps
