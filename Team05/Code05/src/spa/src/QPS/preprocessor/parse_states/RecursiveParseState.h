#pragma once

#include <string>
#include <vector>

#include "ParseState.h"

namespace qps {
class RecursiveParseState : public ParseState {
 public:
  RecursiveParseState(std::string transition,
                      std::string kRecurseDelimiter)
      : ParseState(transition),
        kRecurseDelimiter(kRecurseDelimiter) {}

  inline static Grammar CreateRecurseGrammar(RecursiveParseState &parse_state) {
    return Grammar(
        Grammar::kTrueCheck,
        [&](QueryPtr &query, const std::vector<std::string> &tokens) {
          parse_state.Recurse();
        });
  }

 protected:
  std::string kRecurseDelimiter;
  GrammarItr kRecurseBegin;
  inline void Recurse() {
    if (*itr_ == kRecurseDelimiter) {
      grammar_itr_ = kRecurseBegin;
    } else {
      itr_--;
    }
  }
};
}  // namespace qps
