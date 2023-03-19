#include <vector>

#include "Grammar.h"
#include "QPS/models/PQL.h"
#include "QPS/models/Query.h"

namespace qps {
Grammar::CheckLambda Grammar::kAttrNameCheck = [](std::string token) {
  return AttrRef::is_attr_name(token);
};

Grammar::CheckLambda Grammar::kBooleanCheck = [](std::string token) {
  return token == PQL::kBooleanToken;
};

Grammar::CheckLambda Grammar::kDesignEntityCheck = [](std::string token) {
  return Entity::is_entity_name(token);
};

Grammar::CheckLambda Grammar::kElemCheck = [](std::string token) {
  // synonym | attrRef
  return kSynCheck(token) || AttrRef::is_attr_ref(token);
};

Grammar::CheckLambda Grammar::kEntRefCheck = [](std::string token) {
  // " IDENT " | _ | synonym
  return token == PQL::kQuotationToken
      || kWildcardCheck(token)
      || kSynCheck(token);
};

Grammar::CheckLambda Grammar::kExprCheck = [](std::string token) {
  return PQL::is_wildcard(token)
      || token == PQL::kQuotationToken;
};

Grammar::CheckLambda Grammar::kIdentCheck = [](std::string token) {
  return PQL::is_ident(token);
};

Grammar::CheckLambda Grammar::kRefCheck = [](std::string token) {
  // "IDENT" | INTEGER | synonym (attrRef = synonym '.' attrName)
  return token == PQL::kQuotationToken
      || PQL::is_integer(token)
      || PQL::is_synonym(token);
};

Grammar::CheckLambda Grammar::kRelRefCheck = [](std::string token) {
  return PQL::is_such_that_rel_name(token);
};

Grammar::CheckLambda Grammar::kStmtRefCheck = [](std::string token) {
  // INTEGER | _ | synonym
  return PQL::is_integer(token)
      || kWildcardCheck(token)
      || kSynCheck(token);
};

Grammar::CheckLambda Grammar::kSynCheck = [](std::string token) {
  return PQL::is_synonym(token);
};

Grammar::CheckLambda Grammar::kTupleCheck = [](std::string token) {
  // tuple : elem | '<' elem ( ',' elem)* '>'
  return kElemCheck(token)
      || token == PQL::kTupleOpenBktToken;
};

Grammar::CheckLambda Grammar::kTrueCheck = [](std::string token) {
  return true;
};

Grammar::CheckLambda Grammar::kWildcardCheck = [](std::string token) {
  return PQL::is_wildcard(token);
};

Grammar::ActionLambda Grammar::kEmptyAction = [](
    QueryPtr &query, const std::vector<std::string> &tokens) {};
}  // namespace qps
