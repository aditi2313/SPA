#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <utility>

#include "common/exceptions/QPSExceptions.h"
#include "SP/SourceProcessor.h"
#include "QPS/models/clauses/ClauseType.h"
#include "QPS/models/EntityType.h"
#include "QPS/models/AttrType.h"
#include "models/types.h"

namespace qps {
using EntityName = std::string;
using SynonymName = std::string;
using RelName = std::string;
using AttrName = std::string;
using Elem = std::string;

// Holds all syntax information
class PQL {
 public:
  inline static EntityName kStmtEntityName = "stmt";
  inline static EntityName kReadEntityName = "read";
  inline static EntityName kPrintEntityName = "print";
  inline static EntityName kCallEntityName = "call";
  inline static EntityName kWhileEntityName = "while";
  inline static EntityName kIfEntityName = "if";
  inline static EntityName kAssignEntityName = "assign";
  inline static EntityName kVariableEntityName = "variable";
  inline static EntityName kConstantEntityName = "constant";
  inline static EntityName kProcedureEntityName = "procedure";

  inline static RelName kAffectsRelName = "Affects";
  inline static RelName kAffectsTRelName = "Affects*";
  inline static RelName kModifiesRelName = "Modifies";
  inline static RelName kFollowsRelName = "Follows";
  inline static RelName kFollowsTRelName = "Follows*";
  inline static RelName kPatternRelName = "pattern";
  inline static RelName kUsesRelName = "Uses";
  inline static RelName kParentRelName = "Parent";
  inline static RelName kParentTRelName = "Parent*";
  inline static RelName kCallsRelName = "Calls";
  inline static RelName kCallsTRelName = "Calls*";
  inline static RelName kNextRelName = "Next";
  inline static RelName kNextTRelName = "Next*";
  inline static RelName kWithRelName = "with";

  inline static std::unordered_map<RelName, ClauseType> kRelNameToClauseTypeMap{
      {kAffectsRelName, ClauseType::kAffects},
      {kAffectsTRelName, ClauseType::kAffectsT},
      {kModifiesRelName, ClauseType::kModifies},
      {kFollowsRelName, ClauseType::kFollows},
      {kFollowsTRelName, ClauseType::kFollowsT},
      {kPatternRelName, ClauseType::kPatternAssign},
      {kUsesRelName, ClauseType::kUses},
      {kParentRelName, ClauseType::kParent},
      {kParentTRelName, ClauseType::kParentT},
      {kCallsRelName, ClauseType::kCalls},
      {kCallsTRelName, ClauseType::kCallsT},
      {kNextRelName, ClauseType::kNext},
      {kNextTRelName, ClauseType::kNextT},
      {kWithRelName, ClauseType::kWith}
  };

  inline static ClauseType get_clause_type(RelName const rel_name) {
    return kRelNameToClauseTypeMap.at(rel_name);
  }

  // All relationships that appear after such that
  inline static std::unordered_set<std::string> kAllSuchThatRelNames{
      kAffectsRelName, kAffectsTRelName,
      kCallsRelName, kCallsTRelName,
      kFollowsRelName, kFollowsTRelName,
      kModifiesRelName,
      kNextRelName, kNextTRelName,
      kParentRelName, kParentTRelName,
      kUsesRelName,
  };

  // Returns true if the string is a relationship that appears
  // after such-that.
  // Examples of non such-that rel names are 'pattern' and 'with'
  inline static bool is_such_that_rel_name(std::string const token) {
    return kAllSuchThatRelNames.count(token);
  }

  inline static bool is_synonym(std::string str) {
    return is_ident(str);
  }

  inline static bool is_ident(std::string str) {
    if (str.empty() || !isalpha(str.at(0))) return false;
    for (char c : str) {
      if (!isalnum(c)) return false;
    }
    return true;
  }

  inline static bool is_integer(std::string str) {
    if (str.empty() || str[0] == '0') return false;
    for (char c : str) {
      if (!isdigit(c)) return false;
    }
    return true;
  }

  inline static bool is_wildcard(std::string str) {
    return str == kUnderscoreToken;
  }

  inline static AttrName kProcedureAttrName = "procName";
  inline static AttrName kVariableAttrName = "varName";
  inline static AttrName kValueAttrName = "value";
  inline static AttrName kStmtAttrName = "stmt#";

  inline static std::string kQuotationToken = "\"";
  inline static std::string kSemicolonToken = ";";
  inline static std::string kCommaToken = ",";
  inline static std::string kEqualToken = "=";
  inline static std::string kSelectToken = "Select";
  inline static std::string kSuchToken = "such";
  inline static std::string kThatToken = "that";
  inline static std::string kOpenBktToken = "(";
  inline static std::string kCloseBktToken = ")";
  inline static std::string kAndToken = "and";
  inline static std::string kPeriodToken = ".";
  inline static std::string kBooleanToken = "BOOLEAN";
  inline static std::string kTupleOpenBktToken = "<";
  inline static std::string kTupleCloseBktToken = ">";
  inline static std::string kUnderscoreToken = "_";

  // It is the same string but it is possible for it to change,
  // so these are two separate constants
  inline static std::string kPatternToken = kPatternRelName;
  inline static std::string kWithToken = kWithRelName;
  inline static std::string kAttrRefDelimiter = kPeriodToken;
};
}  // namespace qps
