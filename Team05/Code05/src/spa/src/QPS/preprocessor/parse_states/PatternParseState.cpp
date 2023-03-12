#include "PatternParseState.h"
#include "QPS/factories/MasterClauseFactory.h"

namespace qps {
extern MasterClauseFactory master_clause_factory_;

void PatternParseState::InitializeAssignGrammar() {
  // '('
  assign_grammar_.emplace_back(
      Grammar(
          Grammar::CreateTokenCheck(PQL::kOpenBktToken),
          Grammar::kEmptyAction));

  // argument
  assign_grammar_.emplace_back(
      Grammar(
          Grammar::kArgumentCheck,
          [&](QueryPtr &query) {
            arg2_ = query->CreateArgument(*itr_);
          }));

  // ','
  assign_grammar_.emplace_back(
      Grammar(
          Grammar::CreateTokenCheck(PQL::kCommaToken),
          Grammar::kEmptyAction));

  // expression-spec
  assign_grammar_.emplace_back(
      Grammar(
          Grammar::kExprCheck,
          [&](QueryPtr &query) {
            arg3_ = query->CreateArgument(*itr_);
          }));

  // ')'
  assign_grammar_.emplace_back(
      Grammar(
          Grammar::CreateTokenCheck(PQL::kCloseBktToken),
          [&](QueryPtr &query) {
            if (arg1_ == nullptr || arg2_ == nullptr || arg3_ == nullptr) {
              ThrowException();
            }
            query->add_clause(master_clause_factory_.Create(
                PQL::kModifiesRelName,
                std::move(arg1_->Copy()),
                std::move(arg2_)));
            query->add_clause(master_clause_factory_.Create(
                PQL::kPatternRelName,
                std::move(arg1_),
                std::move(arg3_)));
            
            // Return to main grammar_
            grammar_itr_ = saved_grammar_itr_pos_;
          }));
}
}  // namespace qps