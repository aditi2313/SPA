#pragma once

#include <functional>
#include <string>
#include <vector>

#include "QPS/models/Query.h"

namespace qps {
class Grammar {
 public:
  using CheckLambda = std::function<bool(std::string)>;
  using ActionLambda = std::function<void(
      QueryPtr &, const std::vector<std::string> &)>;

  Grammar(
      CheckLambda check, ActionLambda action)
      : check_(check), action_(action) {}
      
  static CheckLambda kAttrNameCheck;
  static CheckLambda kBooleanCheck;
  static CheckLambda kDesignEntityCheck;
  static CheckLambda kElemCheck;
  static CheckLambda kEntRefCheck;
  static CheckLambda kExprCheck;
  static CheckLambda kIdentCheck;
  static CheckLambda kRefCheck;
  static CheckLambda kRelRefCheck;
  static CheckLambda kSynCheck;
  static CheckLambda kStmtRefCheck;
  static CheckLambda kTupleCheck;
  static CheckLambda kTrueCheck;
  static CheckLambda kWildcardCheck;

  static ActionLambda kEmptyAction;

  inline static CheckLambda CreateTokenCheck(std::string expected_token) {
    return [expected_token](std::string token) {
      return token == expected_token;
    };
  }

  inline bool Check(std::string token) {
    return check_(token);
  }

  inline void Action(
      QueryPtr &query, const std::vector<std::string> &tokens) {
    action_(query, tokens);
  }

 private:
  CheckLambda check_;
  ActionLambda action_;
};

using ParseItr = std::vector<std::string>::iterator;
using GrammarItr = std::vector<Grammar>::iterator;
}  // namespace qps
