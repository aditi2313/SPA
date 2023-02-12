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
  inline static EntityName kStmtEntityId = "stmt";
  inline static EntityName kReadEntityId = "read";
  inline static EntityName kPrintEntityId = "print";
  inline static EntityName kCallEntityId = "call";
  inline static EntityName kWhileEntityId = "while";
  inline static EntityName kIfEntityId = "if";
  inline static EntityName kAssignEntityId = "assign";
  inline static EntityName kVariableEntityId = "variable";
  inline static EntityName kConstantEntityId = "constant";
  inline static EntityName kProcedureEntityId = "procedure";

  inline static std::vector<EntityName> kAllEntityIds{
      kStmtEntityId, kReadEntityId, kPrintEntityId, kCallEntityId,
      kWhileEntityId, kIfEntityId, kAssignEntityId,
      kVariableEntityId, kConstantEntityId, kProcedureEntityId
  };

  inline static bool const is_entity_id(EntityName const token) {
    return find(kAllEntityIds.begin(), kAllEntityIds.end(), token)
        != kAllEntityIds.end();
  }

  inline static EntityName kModifiesRelId = "Modifies";
  inline static EntityName kPatternRelId = "pattern";

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
};
}  // namespace qps
