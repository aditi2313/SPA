#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../models/Query.h"
#include "../models/Grammar.h"
#include "common/exceptions/QPSExceptions.h"

namespace qps {
class ParseState {
 public:
  using ParseItr = std::vector<std::string>::iterator;
  using GrammarItr = std::vector<Grammar>::iterator;

  std::string kTransitionKeyword;

  explicit ParseState(std::string transition)
      : kTransitionKeyword(transition) {}

  virtual void Parse(const std::vector<std::string> &tokens,
                     ParseItr &itr, QueryPtr &query) = 0;
  virtual ~ParseState() = 0;

 protected:
  inline void ThrowException() {
    throw PqlSyntaxErrorException(kExceptionMessage);
  }

  inline virtual bool IsComplete(GrammarItr grammar_itr) {
    for (auto &pos : end_states_) {
      if (grammar_itr == pos) return true;
    }
    return false;
  }

  inline void InitializeGrammar(std::vector<Grammar> grammar) {
    grammar_ = grammar;
    end_states_.push_back(grammar_.end());
  }

  const char *kExceptionMessage;
  std::vector<Grammar> grammar_;
  std::vector<GrammarItr> end_states_;
};

class RecursiveParseState : public ParseState {
 public:
  RecursiveParseState(std::string transition,
                      std::string kRecurseDelimiter)
      : ParseState(transition),
        kRecurseDelimiter(kRecurseDelimiter) {}

 protected:
  std::string kRecurseDelimiter;
  GrammarItr kRecurseBegin;
  void Recurse(ParseItr &itr, GrammarItr &grammar_itr) {
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
                            PQL::kCommaToken) {
    kExceptionMessage = "Invalid PQL syntax in declaration";
    std::vector<Grammar> grammar;

    // design-entity
    grammar.emplace_back(
        Grammar(
            [](std::string token) { return PQL::is_entity_name(token); },
            []() {})
    );
    // synonym
    grammar.emplace_back(
        Grammar(
            Grammar::syn_check_,
            [] {})
    );
    // (
    grammar.emplace_back(
        Grammar(
            [](std::string token) { return token == PQL::kOpenBktToken; },
            [] {})
    );

    kRecurseBegin = next(grammar_.begin());
  }

  void Parse(const std::vector<std::string> &tokens, ParseItr &itr,
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
                            {PQL::kWithToken,
                             PQL::kRefGrammar,
                             PQL::kEqualToken,
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
