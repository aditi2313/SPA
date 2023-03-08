#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../models/Query.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ParseState {
 public:
  using parse_position = std::vector<std::string>::iterator;
  std::string kTransitionKeyword;

  explicit ParseState(std::string transition, std::vector<std::string> grammar)
      : kTransitionKeyword(transition), grammar_(grammar) {
    end_states_.push_back(grammar_.end());
  }

  virtual void Parse(const std::vector<std::string> &tokens,
                     parse_position &itr, QueryPtr &query) = 0;
  virtual ~ParseState() = 0;

 protected:
  const char *kExceptionMessage;
  void ThrowException() { throw PqlSyntaxErrorException(kExceptionMessage); }
  inline virtual bool IsComplete(parse_position grammar_itr) {
    for (auto &pos : end_states_) {
      if (grammar_itr == pos) return true;
    }
    return false;
  }
  std::vector<std::string> grammar_;
  std::vector<parse_position> end_states_;
};

class RecursiveParseState : public ParseState {
 public:
  RecursiveParseState(std::string transition, std::vector<std::string> grammar,
                      std::string kRecurseDelimiter)
      : ParseState(transition, grammar),
        kRecurseDelimiter(kRecurseDelimiter) {}

 protected:
  std::string kRecurseDelimiter;
  parse_position kRecurseBegin;
  void Recurse(parse_position &itr, parse_position &grammar_itr) {
    if (*itr == kRecurseDelimiter) {
      grammar_itr = kRecurseBegin;
    } else {
      grammar_itr++;
      itr--;
    }
  }
};

// design-entity synonym (',' synonym)* ';'
class DeclarationParseState : public RecursiveParseState {
 public:
  DeclarationParseState()
      : RecursiveParseState("",
                            {
                                PQL::kDesignEntityGrammar,
                                PQL::kSynGrammar,
                                PQL::kRecurseGrammar,
                                PQL::kSemicolonToken},
                            PQL::kCommaToken) {
    kExceptionMessage = "Invalid PQL syntax in declaration";
    kRecurseBegin = next(grammar_.begin());
  }

  void Parse(const std::vector<std::string> &tokens, parse_position &itr,
             QueryPtr &query) override;
};

// '<' elem ( ',' elem )* '>'
class TupleParseState : public RecursiveParseState {
 public:
  TupleParseState() :
      RecursiveParseState(PQL::kTupleSelectOpen,
                          {
                              PQL::kTupleSelectOpen,
                              PQL::kElemGrammar,
                              PQL::kRecurseGrammar,
                              PQL::kTupleSelectClose},
                          ",") {
    kExceptionMessage = "Invalid PQL syntax in tuple";
    kRecurseBegin = next(grammar_.begin());
  }

  void Parse(const std::vector<std::string> &tokens, parse_position &itr,
             QueryPtr &query) override;
};

// tuple | BOOLEAN
class SelectParseState : public ParseState {
 public:
  SelectParseState() : ParseState(PQL::kSelectToken,
                                  {
                                      PQL::kSelectToken,
                                      PQL::kSelectGrammar}) {
    kExceptionMessage = "Invalid PQL syntax in select-tuple|boolean";
  }

  void Parse(const std::vector<std::string> &tokens, parse_position &itr,
             QueryPtr &query) override;
 private:
  TupleParseState tuple_parse_state_;
};

// 'such' 'that' relCond
// relCond: relRef ('and' relRef)*
class SuchThatParseState : public RecursiveParseState {
 public:
  SuchThatParseState()
      : RecursiveParseState(PQL::kSuchToken,
                            {
                                PQL::kSuchToken,
                                PQL::kThatToken,
                                PQL::kRelRefGrammar,
                                PQL::kOpenBktToken,
                                PQL::kArgumentGrammar,
                                PQL::kCommaToken,
                                PQL::kArgumentGrammar,
                                PQL::kCloseBktToken,
                                PQL::kRecurseGrammar},
                            PQL::kAndToken) {
    kExceptionMessage = "Invalid PQL syntax in such-that clause";
    kRecurseBegin = next(grammar_.begin(), 2);
    // Allow state to end on PQL::kRecurseGrammar
    end_states_.push_back(prev(grammar_.end()));
  }

  void Parse(const std::vector<std::string> &tokens, parse_position &itr,
             QueryPtr &query) override;
};

// pattern ( 'and' pattern )*
// pattern: 'pattern' syn-assign '(' entRef ',' expression-spec ')'
class PatternParseState : public RecursiveParseState {
 public:
  PatternParseState()
      : RecursiveParseState(PQL::kPatternToken,
                            {
                                PQL::kPatternToken,
                                PQL::kSynGrammar,
                                PQL::kOpenBktToken,
                                PQL::kArgumentGrammar,
                                PQL::kCommaToken,
                                PQL::kExprGrammar,
                                PQL::kCloseBktToken,
                                PQL::kRecurseGrammar},
                            PQL::kAndToken) {
    kExceptionMessage = "Invalid PQL syntax in pattern clause";
    kRecurseBegin = grammar_.begin();
    // Allow state to end on PQL::kRecurseGrammar
    end_states_.push_back(prev(grammar_.end()));
  }

  void Parse(const std::vector<std::string> &tokens, parse_position &itr,
             QueryPtr &query) override;
};

// 'with' attrCompare '(' and ',' attrCompare ')'
class WithParseState : public RecursiveParseState {
 public:
  WithParseState()
      : RecursiveParseState("with",
                            {"with",
                             PQL::kRefGrammar,
                             "=",
                             PQL::kRefGrammar,
                             PQL::kRecurseGrammar},
                            "and") {
    kExceptionMessage = "Invalid PQL syntax in with clause";
    kRecurseBegin = next(grammar_.begin());
    // Allow state to end on PQL::kRecurseGrammar
    end_states_.push_back(prev(grammar_.end()));
  }

  void Parse(const std::vector<std::string> &tokens, parse_position &itr,
             QueryPtr &query) override;
};
}  // namespace qps
