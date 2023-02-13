#pragma once

#include <string>
#include <vector>
#include <memory>
#include "common/Exceptions.h"

#include "../models/Query.h"

namespace qps {
class ParseState {
 public:
  using parse_position = std::vector<std::string>::iterator;
  std::string kTransitionKeyword;

  explicit ParseState(std::string transition) :
      kTransitionKeyword(transition) {}
  virtual std::unique_ptr<Query> parse(
      const std::vector<std::string> &tokens,
      parse_position &itr,
      std::unique_ptr<Query> query) = 0;
  virtual ~ParseState() = 0;
 protected:
  const char *kExceptionMessage;
  void ThrowException() {
    throw PqlSyntaxErrorException(kExceptionMessage);
  }
};

// design-entity synonym (',' synonym)* ';'
class DeclarationParseState : public ParseState {
 public:
  DeclarationParseState() : ParseState("") {
    kExceptionMessage = "Invalid PQL syntax in declaration";
  }

  std::unique_ptr<Query> parse(const std::vector<std::string> &tokens,
                               parse_position &itr,
                               std::unique_ptr<Query> query) override;
};

// synonym (',' synonym)*
class SynonymParseState : public ParseState {
 public:
  SynonymParseState() : ParseState("Select") {
    kExceptionMessage = "Invalid PQL syntax in select-synonym";
  }

  std::unique_ptr<Query> parse(const std::vector<std::string> &tokens,
                               parse_position &itr,
                               std::unique_ptr<Query> query) override;
};

// 'such' 'that' relRef
class SuchThatParseState : public ParseState {
 public:
  SuchThatParseState() : ParseState("such") {
    kExceptionMessage = "Invalid PQL syntax in such-that clause";
  }

  std::unique_ptr<Query> parse(const std::vector<std::string> &tokens,
                               parse_position &itr,
                               std::unique_ptr<Query> query) override;
};

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
class PatternParseState : public ParseState {
 public:
  PatternParseState() : ParseState("pattern") {
    kExceptionMessage = "Invalid PQL syntax in pattern clause";
  }

  std::unique_ptr<Query> parse(const std::vector<std::string> &tokens,
                               parse_position &itr,
                               std::unique_ptr<Query> query) override;
};
}  // namespace qps
