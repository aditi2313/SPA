#include "ParseState.h"

namespace qps {
void ParseState::Parse(
    const std::vector<std::string> &tokens,
    ParseItr &itr,
    QueryPtr &query) {
  grammar_itr_ = grammar_.begin();
  itr_ = itr;

  while (itr_ != tokens.end() && grammar_itr_ != grammar_.end()) {
    auto &grammar = *grammar_itr_;
    if (!grammar.Check(*itr_)) ThrowException();

    grammar_itr_++;
    // Action needs to be performed AFTER incrementing
    // grammar_itr such that should the action be Recurse,
    // grammar_itr is correctly set to kRecurseBegin.
    grammar.Action(query);
    itr_++;
  }

  if (!IsComplete(grammar_itr_)) ThrowException();
  itr = itr_;
}
}