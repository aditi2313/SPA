#include "Grammar.h"
#include "QPS/models/PQL.h"
#include "QPS/models/Query.h"

namespace qps {
Grammar::CheckLambda Grammar::kArgumentCheck = [](std::string token) {
  return PQL::is_argument(token);
};

Grammar::CheckLambda Grammar::kAttrNameCheck = [](std::string token) {
  return PQL::is_attr_name(token);
};

Grammar::CheckLambda Grammar::kBooleanCheck = [](std::string token) {
  return token == PQL::kBooleanToken;
};

Grammar::CheckLambda Grammar::kDesignEntityCheck = [](std::string token) {
  return PQL::is_entity_name(token);
};

Grammar::CheckLambda Grammar::kElemCheck = [](std::string token) {
  // synonym | attrRef
  return kSynCheck(token) || PQL::is_attr_ref(token);
};

Grammar::CheckLambda Grammar::kExprCheck = [](std::string token) {
  return PQL::is_pattern_wildcard(token)
      || PQL::is_pattern_exact(token)
      || PQL::is_wildcard(token);
};

Grammar::CheckLambda Grammar::kExactExprCheck = [](std::string token) {
  return PQL::is_pattern_exact(token);
};

Grammar::CheckLambda Grammar::kRefCheck = [](std::string token) {
  // "IDENT" | INTEGER | attrRef
  return PQL::is_ident_arg(token)
      || PQL::is_integer(token)
      || PQL::is_attr_ref(token);
};

Grammar::CheckLambda Grammar::kRelRefCheck = [](std::string token) {
  return PQL::is_such_that_rel_name(token);
};

Grammar::CheckLambda Grammar::kSynCheck = [](std::string token) {
  return PQL::is_synonym(token);
};

Grammar::CheckLambda Grammar::kTupleCheck = [](std::string token) {
  // tuple : elem | '<' elem ( ',' elem)* '>'
  return kElemCheck(token)
      || token == PQL::kTupleOpenBktToken;
};

Grammar::CheckLambda Grammar::kWildcardCheck = [](std::string token) {
  return PQL::is_wildcard(token);
};

Grammar::ActionLambda Grammar::kEmptyAction = [](QueryPtr &query) {};
}  // namespace qps
