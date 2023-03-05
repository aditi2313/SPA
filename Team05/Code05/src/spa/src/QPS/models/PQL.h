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

  inline static bool const is_entity_name(EntityName const str) {
    return kAllEntityNames.count(str) == 1;
  }

  inline static std::string kBooleanSelect = "BOOLEAN";
  inline static std::string kTupleSelectOpen = "<";
  inline static std::string kTupleSelectClose = ">";

  inline static RelName kModifiesRelName = "Modifies";
  inline static RelName kFollowsRelName = "Follows";
  inline static RelName kFollowsTRelName = "Follows*";
  inline static RelName kPatternRelName = "pattern";
  inline static RelName kUsesRelName = "Uses";
  inline static RelName kParentRelName = "Parent";
  inline static RelName kParentTRelName = "Parent*";

  inline static std::unordered_set<std::string> kAllRelNames{
      kModifiesRelName, kFollowsRelName, kFollowsTRelName, kParentRelName,
      kParentTRelName, kUsesRelName, kPatternRelName
  };

  inline static bool is_rel_name(std::string const token) {
    return kAllRelNames.find(token) != kAllRelNames.end();
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

  inline static std::string kSemicolonToken = ";";
  inline static std::string kCommaToken = ",";
  inline static std::string kSelectToken = "Select";
  inline static std::string kSuchToken = "such";
  inline static std::string kThatToken = "that";
  inline static std::string kOpenBktToken = "(";
  inline static std::string kCloseBktToken = ")";
  inline static std::string kAndToken = "and";
  // It is the same string but it is possible for it to change
  // so these are two separate constants
  inline static std::string kPatternToken = kPatternRelName;

  // Grammars are tokens with special meaning and actions
  // attached to them. They are not meant to be compared
  // literally.
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
      return is_rel_name(token);
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
          || CheckGrammar(token, kBooleanGrammar)
          || token == kTupleSelectOpen;
    } else {
      return token == grammar;
    }
  }
};
}  // namespace qps
