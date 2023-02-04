#include <sstream>
#include <iostream>

#include "Parser.h"

namespace qps {

bool Parser::ShouldGoToNextState(int current_state_index, std::string token) {
  if (current_state_index >= states_.size() - 1) return false;  // last stage
  return token == states_.at(current_state_index + 1)->kTransitionKeyword;
}

// Returns a vector of tokens retrieved from query_string
std::vector<std::string> Parser::PreprocessQueryString(std::string query_string) {
  // First insert whitespaces around special characters
  // (e.g. semicolons and brackets) for easier delimitation
  std::string new_query = "";
  std::string special_characters = ";(),";
  for (auto itr = query_string.begin(); itr != query_string.end(); ++itr) {
    if (special_characters.find(*itr) != std::string::npos) {
      new_query += " " + std::string(1, *itr) + " ";
    } else if (*itr == '\"') {
      // This removes whitespace in the pattern match arg
      // e.g "x + y" such that it is treated as one token.
      itr++;
      while (*itr != '\"') {
        if (*itr == ' ') {
          itr++;
          continue;
        }
        new_query += *itr++;
      }
    } else {
      new_query += *itr;
    }
  }

  std::stringstream ss(new_query);
  std::vector<std::string> tokens;
  std::string token;
  while (ss >> token) {
    // Separates query string by whitespace.
    // Works for multiple whitespaces too.
    tokens.push_back(token);
  }

  return tokens;
}

Query Parser::ParseQuery(std::string query_string) {
  Query query;
  std::vector<std::string> tokens = PreprocessQueryString(query_string);

  int current_state_index = 0;
  auto itr = tokens.begin();
  while (itr != tokens.end()) {
    if (ShouldGoToNextState(current_state_index, *itr)) {
      current_state_index++;
      continue;  // go to next state
    }
    itr = states_.at(current_state_index)->parse(tokens, itr, &query);
  }

  return query;
}
}  // namespace qps
