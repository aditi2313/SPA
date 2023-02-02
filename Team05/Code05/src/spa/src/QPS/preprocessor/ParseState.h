#pragma once

#include <string>

#include "../models/Query.h"

namespace qps {

class ParseState {
 public:
  using parse_position = std::vector<std::string>::iterator;
  std::string kTransitionKeyword;

  ParseState(std::string transition) : kTransitionKeyword(transition) {};
  virtual parse_position parse(
      std::vector<std::string> &tokens,
      parse_position itr,
      Query &query
  ) = 0;
  virtual ~ParseState() = 0;
};

// design-entity synonym (',' synonym)* ';'
class DeclarationParseState : public ParseState {
 public:
  DeclarationParseState() : ParseState("") {};

  parse_position parse(std::vector<std::string> &tokens,
                       parse_position itr,
                       Query &query) override;
};

// syn
class SynonymParseState : public ParseState {
 public:
  SynonymParseState() : ParseState("Select") {};

  parse_position parse(std::vector<std::string> &tokens,
                       parse_position itr,
                       Query &query) override;
};

// 'such' 'that' relRef
class SuchThatParseState : public ParseState {
 public:
  SuchThatParseState() : ParseState("such") {};

  parse_position parse(std::vector<std::string> &tokens,
                       parse_position itr,
                       Query &query) override;
};

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
class PatternParseState : public ParseState {
 public:
  PatternParseState() : ParseState("pattern") {};

  parse_position parse(std::vector<std::string> &tokens,
                       parse_position itr,
                       Query &query) override;
};
}  // namespace qps
