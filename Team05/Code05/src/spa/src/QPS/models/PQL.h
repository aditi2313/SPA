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

  inline static std::vector<std::string> kAllEntityName{
      kStmtEntityName, kReadEntityName, kPrintEntityName, kCallEntityName,
      kWhileEntityName, kIfEntityName, kAssignEntityName,
      kVariableEntityName, kConstantEntityName, kProcedureEntityName
  };

  inline static bool const is_entity_name(std::string const token) {
    return find(kAllEntityName.begin(), kAllEntityName.end(), token)
        != kAllEntityName.end();
  }

  inline static EntityName kModifiesRelId = "Modifies";
  inline static EntityName kPatternRelId = "pattern";
  inline static EntityName kUsesRelId = "Uses";
  inline static EntityName kParentRelId = "Parent";

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
};
}  // namespace qps
