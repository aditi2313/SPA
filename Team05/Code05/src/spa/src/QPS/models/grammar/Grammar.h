#pragma once

#include <functional>
#include <string>

#include "QPS/models/Query.h"

namespace qps {
class Grammar {
 public:
  using CheckLambda = std::function<bool(std::string)>;
  using ActionLambda = std::function<void(QueryPtr &)>;

  Grammar(
      CheckLambda check, ActionLambda action)
      : check_(check), action_(action) {}

  static CheckLambda kArgumentCheck;
  static CheckLambda kAttrNameCheck;
  static CheckLambda kBooleanCheck;
  static CheckLambda kDesignEntityCheck;
  static CheckLambda kElemCheck;
  static CheckLambda kExactExprCheck;
  static CheckLambda kExprCheck;
  static CheckLambda kRefCheck;
  static CheckLambda kRelRefCheck;
  static CheckLambda kSynCheck;
  static CheckLambda kTupleCheck;
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

  inline void Action(QueryPtr &query) {
    action_(query);
  }

 private:
  CheckLambda check_;
  ActionLambda action_;
};

using ParseItr = std::vector<std::string>::iterator;
using GrammarItr = std::vector<Grammar>::iterator;
}  // namespace qps
