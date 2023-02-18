#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "common/Exceptions.h"

#include "../models/Query.h"

namespace qps {
class ParseState {
 public:
  using parse_position = std::vector<std::string>::iterator;
  std::string kTransitionKeyword;

  explicit ParseState(
      std::string transition, std::vector<std::string> grammar) :
      kTransitionKeyword(transition), grammar_(grammar) {}

  virtual void parse(
      const std::vector<std::string> &tokens,
      parse_position &itr,
      QueryPtr &query) = 0;
  virtual ~ParseState() = 0;
 protected:
  const char *kExceptionMessage;
  void ThrowException() {
    throw PqlSyntaxErrorException(kExceptionMessage);
  }
  inline virtual bool IsComplete(parse_position grammar_itr) {
    return grammar_itr == grammar_.end();
  }
  std::vector<std::string> grammar_;
};

class RecursiveParseState : public ParseState {
 public:
  RecursiveParseState(
      std::string transition,
      std::vector<std::string> grammar,
      std::string kRecurseDelimiter)
      : ParseState(transition, grammar), kRecurseDelimiter(kRecurseDelimiter) {}

 protected:
  std::string kRecurseDelimiter;
  virtual parse_position recurse() = 0;
  inline bool CheckRecurseDelimiter(std::string token) {
    return token == kRecurseDelimiter;
  }
};

// design-entity synonym (',' synonym)* ';'
class DeclarationParseState : public RecursiveParseState {
 public:
  DeclarationParseState() : RecursiveParseState("", {
      PQL::kDesignEntityGrammar, PQL::kSynGrammar, PQL::kRecurseGrammar, ";"
  }, ",") {
    kExceptionMessage = "Invalid PQL syntax in declaration";
  }

  void parse(const std::vector<std::string> &tokens,
             parse_position &itr,
             QueryPtr &query) override;
 private:
  parse_position recurse() override {
    return grammar_.begin();
  }
};

// synonym | tuple | BOOLEAN
class SelectParseState : public ParseState {
 public:
  SelectParseState() : ParseState("Select", {
      "Select", PQL::kSynGrammar
  }) {
    kExceptionMessage = "Invalid PQL syntax in select-synonym";
  }

  void parse(const std::vector<std::string> &tokens,
             parse_position &itr,
             QueryPtr &query) override;
};

// 'such' 'that' relRef
class SuchThatParseState : public ParseState {
 public:
  SuchThatParseState() : ParseState("such", {
      "such", "that", PQL::kRelRefGrammar,
      "(", PQL::kArgumentGrammar, ",", PQL::kArgumentGrammar, ")"
  }) {
    kExceptionMessage = "Invalid PQL syntax in such-that clause";
  }

  void parse(const std::vector<std::string> &tokens,
             parse_position &itr,
             QueryPtr &query) override;
};

// 'pattern' syn-assign '(' entRef ',' expression-spec ')'
class PatternParseState : public ParseState {
 public:
  PatternParseState() : ParseState("pattern", {
      "pattern", PQL::kSynGrammar,
      "(", PQL::kArgumentGrammar, ",", PQL::kExprGrammar, ")"
  }) {
    kExceptionMessage = "Invalid PQL syntax in pattern clause";
  }

  void parse(const std::vector<std::string> &tokens,
             parse_position &itr,
             QueryPtr &query) override;
};
}  // namespace qps
