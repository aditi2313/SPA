#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "common/Exceptions.h"
#include "models/types.h"

using models::EntityName;

namespace qps {

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

  inline static std::vector<std::string> kAllEntityNames{
      kStmtEntityName, kReadEntityName, kPrintEntityName, kCallEntityName,
      kWhileEntityName, kIfEntityName, kAssignEntityName,
      kVariableEntityName, kConstantEntityName, kProcedureEntityName
  };

  inline static bool const is_entity_name(std::string const token) {
    return find(kAllEntityNames.begin(), kAllEntityNames.end(), token)
        != kAllEntityNames.end();
  }

  inline static EntityName kRelRefGrammar = "relRef";
  inline static EntityName kArgumentGrammar = "arg";
  inline static EntityName kSynGrammar = "syn";
  inline static EntityName kExprGrammar = "exp";

  inline static EntityName kModifiesRelId = "Modifies";
  inline static EntityName kFollowsRelId = "Follows";
  inline static EntityName kFollowsTRelId = "Follows*";
  inline static EntityName kPatternRelId = "pattern";

  inline static std::vector<std::string> kAllRelIds{
      kModifiesRelId, kFollowsRelId, kFollowsTRelId, kPatternRelId
  };

  inline static bool is_rel_ref(std::string const token) {
    return find(kAllRelIds.begin(), kAllRelIds.end(), token)
        != kAllRelIds.end();
  }

  inline static bool is_argument(std::string const token) {
    return is_ident(token) || is_integer(token) || is_wildcard(token);
  }

  inline static bool is_ident(std::string str) {
    if (str.empty() || !isalpha(str[0])) return false;
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

  inline static bool is_pattern_wildcard(std::string str) {
    if (str.size() < 2) return false;
    return str.front() == '_' && str.back() == '_';
  }

  inline static bool CheckGrammar(std::string const token, std::string const grammar) {
    if (grammar == kArgumentGrammar) {
      return is_argument(token);
    } else if (grammar == kRelRefGrammar) {
      return is_rel_ref(token);
    } else if (grammar == kSynGrammar) {
      return is_ident(token);
    } else if (grammar == kExprGrammar) {
      return true;
    } else {
      return token == grammar;
    }
  }
};
}  // namespace qps
