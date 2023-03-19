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

  inline static std::unordered_set<std::string> kAllEntityNames{
      kStmtEntityName, kReadEntityName, kPrintEntityName, kCallEntityName,
      kWhileEntityName, kIfEntityName, kAssignEntityName,
      kVariableEntityName, kConstantEntityName, kProcedureEntityName
  };

  inline static std::unordered_set<EntityType> kAllEntityTypes{
      EntityType::kStmt, EntityType::kRead,
      EntityType::kPrint, EntityType::kCall,
      EntityType::kWhile, EntityType::kIf, EntityType::kAssign,
      EntityType::kVariable, EntityType::kConstant, EntityType::kProcedure
  };

  inline static std::unordered_set<EntityType> kAllStmtEntityTypes{
      EntityType::kStmt, EntityType::kRead,
      EntityType::kPrint, EntityType::kCall,
      EntityType::kWhile, EntityType::kIf, EntityType::kAssign
  };

  inline static std::unordered_map<EntityName, EntityType>
      kEntityNameToEntityTypeMap{
      {kStmtEntityName, EntityType::kStmt},
      {kReadEntityName, EntityType::kRead},
      {kPrintEntityName, EntityType::kPrint},
      {kCallEntityName, EntityType::kCall},
      {kWhileEntityName, EntityType::kWhile},
      {kIfEntityName, EntityType::kIf},
      {kAssignEntityName, EntityType::kAssign},
      {kVariableEntityName, EntityType::kVariable},
      {kConstantEntityName, EntityType::kConstant},
      {kProcedureEntityName, EntityType::kProcedure}
  };

  inline static bool const is_entity_name(EntityName const entity_name) {
    return kAllEntityNames.count(entity_name);
  }

  inline static EntityType get_entity_type(EntityName const entity_name) {
    return kEntityNameToEntityTypeMap.at(entity_name);
  }

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
    return str == "_";
  }

  inline static AttrName kProcedureAttrName = "procName";
  inline static AttrName kVariableAttrName = "varName";
  inline static AttrName kValueAttrName = "value";
  inline static AttrName kStmtAttrName = "stmt#";
  // Maps an AttrName (e.g stmt#) to a hashset of all
  // entities that can be paired with that AttrName.
  // e.g. varName is mapped to { variable, read, print }
  inline static std::unordered_map<AttrType, std::unordered_set<EntityType>>
      kAttrTypeToEntitiesMap{
      {AttrType::kProcName, {EntityType::kProcedure, EntityType::kCall}},
      {AttrType::kVarName,
       {EntityType::kVariable, EntityType::kRead, EntityType::kPrint}},
      {AttrType::kValue, {EntityType::kConstant}},
      {AttrType::kStmtNum, kAllStmtEntityTypes}
  };

  inline static std::unordered_map<AttrName, AttrType> kAttrNameToTypeMap{
      {kProcedureAttrName, AttrType::kProcName},
      {kVariableAttrName, AttrType::kVarName},
      {kValueAttrName, AttrType::kValue},
      {kStmtAttrName, AttrType::kStmtNum}
  };

  inline static std::unordered_map<AttrType, AttrName> kAttrTypeToNameMap{
      {AttrType::kProcName, kProcedureAttrName},
      {AttrType::kVarName, kVariableAttrName},
      {AttrType::kValue, kValueAttrName},
      {AttrType::kStmtNum, kStmtAttrName}
  };

  inline static AttrType get_attr_type(AttrName attr_name) {
    return kAttrNameToTypeMap.at(attr_name);
  }

  inline static std::unordered_set<std::string> kAllAttrName{
      kProcedureAttrName, kVariableAttrName,
      kValueAttrName, kStmtAttrName
  };

  inline static bool is_attr_name(std::string str) {
    return kAllAttrName.count(str);
  }

  inline static bool is_attr_ref(std::string str) {
    auto index = str.find(kAttrRefDelimiter);
    // "." doesn't exist
    if (index == std::string::npos) return false;
    auto [syn, attr_name] = split_attr_ref(str);
    return is_synonym(syn)
        && is_attr_name(attr_name);
  }

  inline static bool ValidateAttrRef(
      AttrType attr_type, EntityType entity_type) {
    auto &attr_name_types = kAttrTypeToEntitiesMap.at(attr_type);
    return attr_name_types.count(entity_type);
  }

  // Splits an attrRef (e.g s.stmt#) by the '.' delimiter
  // Returns a pair of strings [ syn_name, attr_name ]
  // that is before and after the delimiter respectively.
  inline static std::pair<std::string, std::string> split_attr_ref(
      std::string str) {
    auto index = str.find(kAttrRefDelimiter);
    std::string syn_name = str.substr(0, index);
    std::string attr_name = str.substr(index + 1);
    return {syn_name, attr_name};
  }

  // Given a syn_name and attr_name, joins attrRef back together
  inline static std::string join_attr_ref(
      SynonymName syn_name, AttrType attr_type
  ) {
    return syn_name
        + kAttrRefDelimiter
        + kAttrTypeToNameMap.at(attr_type);
  }

  // Give an AttrType, return true if its type is IDENT.
  // Note that this does not have to correspond to the type of
  // the synonym.
  // E.g read.varName is IDENT even though read is a stmt
  // and stmt is an INTEGER type.
  inline static bool is_attr_type_ident(AttrType attr_type) {
    return attr_type == AttrType::kProcName
        || attr_type == AttrType::kVarName;
  }

  // Give an AttrName, return true if its type is INTEGER.
  inline static bool is_attr_type_integer(AttrType attr_type) {
    return attr_type == AttrType::kValue
        || attr_type == AttrType::kStmtNum;
  }

  // A secondary attr_ref is defined as an attr_ref that is
  // not the same as its index.
  // E.g stmt.stmt# is the same as its index, but
  // call.procName is not the same.
  // In ADVANCED SPA requirements, only
  // call, print, and read can have secondary attr_refs.
  inline static bool is_attr_ref_secondary(
      EntityType entity_type, AttrType attr_type) {
    switch (entity_type) {
      case EntityType::kRead:
      case EntityType::kPrint: {
        return attr_type == AttrType::kVarName;
      }
      case EntityType::kCall: {
        return attr_type == AttrType::kProcName;
      }
      default: {
        return false;
      }
    }
  }

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
