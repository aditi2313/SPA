#pragma once

#include <string>
#include <unordered_set>
#include <memory>
#include <utility>

#include "common/exceptions/QPSExceptions.h"
#include "SP/SourceProcessor.h"
#include "models/types.h"

using models::EntityName;

namespace qps {
class PQL {
 public:
  using RelName = std::string;

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

  inline static bool const is_entity_name(std::string const token) {
    return kAllEntityNames.count(token) == 1;
  }

  inline static EntityName const get_base_entity_name(
      EntityName const entity_name) {
    if (kAllStmtEntityNames.count(entity_name)) {
      return kStmtEntityName;
    }
    return entity_name;
  }

  inline static RelName kModifiesRelId = "Modifies";
  inline static RelName kFollowsRelId = "Follows";
  inline static RelName kFollowsTRelId = "Follows*";
  inline static RelName kPatternRelId = "pattern";
  inline static RelName kUsesRelId = "Uses";
  inline static RelName kParentRelId = "Parent";
  inline static RelName kParentTRelId = "Parent*";

  inline static std::string kBooleanSelect = "BOOLEAN";

  inline static std::unordered_set<std::string> kAllRelIds{
      kModifiesRelId, kFollowsRelId, kFollowsTRelId, kParentRelId,
      kParentTRelId, kUsesRelId, kPatternRelId
  };

  inline static bool is_rel_ref(std::string const token) {
    return kAllRelIds.find(token) != kAllRelIds.end();
  }

  inline static bool is_argument(std::string const token) {
    return is_ident(token)
        || is_integer(token)
        || is_wildcard(token)
        || is_pattern_exact(token)
        || is_pattern_wildcard(token)
        || is_ident_arg(token);
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

  inline static std::string kRelRefGrammar = "relRef";
  inline static std::string kArgumentGrammar = "arg";
  inline static std::string kSynGrammar = "syn";
  inline static std::string kExprGrammar = "exp";
  inline static std::string kDesignEntityGrammar = "designEntity";
  inline static std::string kRecurseGrammar = "*";
  inline static std::string kBooleanGrammar = "boolean";
  inline static std::string kSelectGrammar = "select";

  inline static bool CheckGrammar(
      std::string const token, std::string const grammar) {
    if (grammar == kArgumentGrammar) {
      return is_argument(token);
    } else if (grammar == kRelRefGrammar) {
      return is_rel_ref(token);
    } else if (grammar == kSynGrammar) {
      return is_ident(token);
    } else if (grammar == kDesignEntityGrammar) {
      return is_entity_name(token);
    } else if (grammar == kExprGrammar) {
      return is_pattern_wildcard(token)
          || is_pattern_exact(token)
          || is_wildcard(token);
    } else if (grammar == kRecurseGrammar) {
      return true;
    } else if (grammar == kBooleanGrammar) {
      return token == kBooleanSelect;
    } else if (grammar == kSelectGrammar) {
      // tuple | BOOLEAN
      return CheckGrammar(token, kSynGrammar)
          || CheckGrammar(token, kBooleanGrammar);
    } else {
      return token == grammar;
    }
  }
};
}  // namespace qps
