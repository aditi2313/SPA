#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <utility>

#include "common/exceptions/QPSExceptions.h"
#include "SP/SourceProcessor.h"
#include "models/types.h"

namespace qps {
using EntityName = std::string;
using SynonymName = std::string;
using RelName = std::string;
using AttrName = std::string;
using AttrRef = std::string;
using Elem = std::string;

class PQL {
 public:
  inline static std::string kStmtEntityName = "stmt";
  inline static std::string kReadEntityName = "read";
  inline static std::string kPrintEntityName = "print";
  inline static std::string kCallEntityName = "call";
  inline static std::string kWhileEntityName = "while";
  inline static std::string kIfEntityName = "if";
  inline static std::string kAssignEntityName = "assign";
  inline static std::string kVariableEntityName = "variable";
  inline static std::string kConstantEntityName = "constant";
  inline static std::string kProcedureEntityName = "procedure";

  inline static std::unordered_set<std::string> kAllEntityNames{
      kStmtEntityName, kReadEntityName, kPrintEntityName, kCallEntityName,
      kWhileEntityName, kIfEntityName, kAssignEntityName,
      kVariableEntityName, kConstantEntityName, kProcedureEntityName
  };

  inline static std::unordered_set<std::string> kAllStmtEntityNames{
      kStmtEntityName, kReadEntityName, kPrintEntityName, kCallEntityName,
      kWhileEntityName, kIfEntityName, kAssignEntityName
  };

  inline static bool const is_entity_name(EntityName const str) {
    return kAllEntityNames.count(str);
  }

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
  inline static RelName kWithRelName = "with";

  // All relationships that appear after such that
  inline static std::unordered_set<std::string> kAllSuchThatRelNames{
      kModifiesRelName, kFollowsRelName, kFollowsTRelName, kParentRelName,
      kParentTRelName, kUsesRelName, kPatternRelName,
      kCallsRelName, kCallsTRelName, kNextRelName
  };

  // Returns true if the string is a relationship that appears
  // after such-that.
  // Examples of non such-that rel names are 'pattern' and 'with'
  inline static bool is_such_that_rel_name(std::string const token) {
    return kAllSuchThatRelNames.count(token);
  }

  inline static bool is_argument(std::string const token) {
    return is_ident(token)
        || is_integer(token)
        || is_wildcard(token)
        || is_pattern_exact(token)
        || is_pattern_wildcard(token)
        || is_ident_arg(token);
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

  inline static bool is_ident_arg(std::string str) {
    if (str.size() < 3) return false;
    if (str.front() != '\"' || str.back() != '\"') return false;
    return is_ident(str.substr(1, str.size() - 2));
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

  inline static bool is_pattern_exact(std::string str) {
    if (str.size() < 2) return false;
    return str.front() == '\"' && str.back() == '\"';
  }

  inline static bool is_pattern_wildcard(std::string str) {
    if (str.size() < 2) return false;
    return str.front() == '_'
        && str.back() == '_'
        && is_pattern_exact(str.substr(1, str.size() - 2));
  }

  inline static AttrName kProcedureAttrName = "procName";
  inline static AttrName kVariableAttrName = "varName";
  inline static AttrName kValueAttrName = "value";
  inline static AttrName kStmtAttrName = "stmt#";
  // Maps an AttrName (e.g stmt#) to a hashset of all
  // entities that can be paired with that AttrName.
  // e.g. varName is mapped to { variable, read, print }
  inline static std::unordered_map<std::string, std::unordered_set<EntityName>>
      kAttrNameToEntitiesMap{
      {kProcedureAttrName, {kProcedureEntityName, kCallEntityName}},
      {kVariableAttrName,
       {kVariableEntityName, kReadEntityName, kPrintEntityName}},
      {kValueAttrName, {kConstantEntityName}},
      {kStmtAttrName, kAllStmtEntityNames}
  };

  inline static std::unordered_set<std::string> kAllAttrName{
      kProcedureAttrName, kVariableAttrName,
      kValueAttrName, kStmtAttrName
  };

  inline static bool is_attr_name(std::string str) {
    return kAllAttrName.count(str);
  }

  inline static bool is_attr_ref(std::string str) {
    auto index = str.find('.');
    // "." doesn't exist
    if (index == std::string::npos) return false;
    auto [syn, attr_name] = split_attr_ref(str);
    return is_synonym(syn)
        && is_attr_name(attr_name);
  }

  inline static bool ValidateAttrRef(
      AttrName attr_name, EntityName entity_name) {
    std::cout << attr_name << " " << entity_name << "\n";
    auto &attr_name_types = kAttrNameToEntitiesMap.at(attr_name);
    return attr_name_types.count(entity_name);
  }

  inline static std::string kSemicolonToken = ";";
  inline static std::string kCommaToken = ",";
  inline static std::string kPeriodToken = ".";
  inline static std::string kEqualToken = "=";
  inline static std::string kSelectToken = "Select";
  inline static std::string kSuchToken = "such";
  inline static std::string kThatToken = "that";
  inline static std::string kOpenBktToken = "(";
  inline static std::string kCloseBktToken = ")";
  inline static std::string kAndToken = "and";
  inline static std::string kBooleanToken = "BOOLEAN";
  inline static std::string kTupleOpenBktToken = "<";
  inline static std::string kTupleCloseBktToken = ">";

  // It is the same string but it is possible for it to change,
  // so these are two separate constants
  inline static std::string kPatternToken = kPatternRelName;
  inline static std::string kWithToken = kWithRelName;
  inline static std::string kAttrRefDelimiter = kPeriodToken;

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
      SynonymName syn_name, AttrName attr_name
  ) {
    return syn_name + kAttrRefDelimiter + attr_name;
  }

  // Give an AttrName, return true if its type is IDENT.
  // Note that this does not have to correspond to the type of
  // the synonym.
  // E.g read.varName is IDENT even though read is a stmt
  // and stmt is an INTEGER type.
  inline static bool is_attr_name_ident(AttrName attr_name) {
    return attr_name == kProcedureAttrName
        || attr_name == kVariableAttrName;
  }

  // Give an AttrName, return true if its type is INTEGER.
  inline static bool is_attr_name_integer(AttrName attr_name) {
    return attr_name == kValueAttrName
        || attr_name == kStmtAttrName;
  }

  // A secondary attr_ref is defined as an attr_ref that is
  // not the same as its index.
  // E.g stmt.stmt# is the same as its index, but
  // call.procName is not the same.
  // In ADVANCED SPA requirements, only
  // call, print, and read can have secondary attr_refs.
  inline static bool is_attr_ref_secondary(
      EntityName entity_name, AttrName attr_name) {
    if (entity_name == kReadEntityName
        || entity_name == kPrintEntityName) {
      return attr_name == kVariableAttrName;
    }
    if (entity_name == kCallEntityName) {
      return attr_name == kProcedureAttrName;
    }
    return false;  // False by default
  }
};
}  // namespace qps
