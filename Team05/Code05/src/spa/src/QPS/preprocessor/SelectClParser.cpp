#include <sstream>
#include <utility>

#include "SelectClParser.h"

namespace qps {

// Compares token with the transition keyword of the next stage
// to determine if the machine should go to next state
int SelectClParser::NextState(
    int current_state_index, std::string token) {
  for (int neighbour : transition_table_[current_state_index]) {
    if (token == states_.at(neighbour)->kTransitionKeyword) {
      return neighbour;
    }
  }

  return current_state_index;  // Stay in same state
}

// Returns a vector of tokens retrieved from query_string
std::vector<std::string> SelectClParser::PreprocessQueryString(
    std::string query_string) {
  // First insert whitespaces around special characters
  // (e.g. semicolons and brackets) for easier delimitation
  std::string new_query = "";
  std::string special_characters = ";(),<>";
  for (auto itr = query_string.begin(); itr != query_string.end(); ++itr) {
    if (special_characters.find(*itr) != std::string::npos) {
      new_query += " " + std::string(1, *itr) + " ";
    } else if (*itr == '\"') {
      // This removes whitespace in the pattern match arg
      // e.g "x + y" such that it is treated as one token.
      new_query += *itr++;
      while (*itr != '\"') {
        if (*itr == ' ') {
          itr++;
          continue;
        }
        new_query += *itr++;
      }
      new_query += *itr;
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

// Parses query based on states
std::unique_ptr<Query> SelectClParser::ParseQuery(std::string query_string) {
  std::unique_ptr<Query> query = std::make_unique<Query>();
  std::vector<std::string> tokens = PreprocessQueryString(query_string);

  int current_state_index = 0;
  auto itr = tokens.begin();
  while (itr != tokens.end()) {
    current_state_index = NextState(current_state_index, *itr);
    states_.at(current_state_index)->Parse(
        tokens, itr, query);
  }

  return query;
}
}  // namespace qps
