#include <sstream>
#include <utility>

#include "SelectClParser.h"

namespace qps {

// Compares token with the transition keyword of the next stage
// to determine if the machine should go to next state
int SelectClParser::NextState(
    int current_state_index, std::string token) {
  for (int next_state : transition_table_.at(current_state_index)) {
    if (states_.at(next_state)->is_transition_keyword(token)) {
      return next_state;
    }
  }

  throw PqlSyntaxErrorException("Invalid PQL syntax");
}

// Returns a vector of tokens retrieved from query_string
std::vector<std::string> SelectClParser::PreprocessQueryString(
    std::string query_str) {
  query_str = PadWhitespaces(query_str);

  std::stringstream ss(query_str);
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

std::string SelectClParser::PadWhitespaces(std::string query_str) {
  std::string new_query = "";

  // Pad whitespaces around special characters
  for (auto itr = query_str.begin(); itr != query_str.end(); ++itr) {
    if (special_characters_.count(std::string(1, *itr))) {
      new_query += " " + std::string(1, *itr) + " ";
    } else {
      new_query += *itr;
    }
  }

  return new_query;
}
}  // namespace qps
