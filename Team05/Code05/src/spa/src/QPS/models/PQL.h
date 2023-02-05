#pragma once

#include <string>
#include <vector>

#include "common/Exceptions.h"
#include "models/types.h"
#include "Clause.h"

using models::EntityId;

namespace qps {

class PQL {
 public:
  inline static EntityId kStmtEntityId = "stmt";
  inline static EntityId kReadEntityId = "read";
  inline static EntityId kPrintEntityId = "print";
  inline static EntityId kCallEntityId = "call";
  inline static EntityId kWhileEntityId = "while";
  inline static EntityId kIfEntityId = "if";
  inline static EntityId kAssignEntityId = "assign";
  inline static EntityId kVariableEntityId = "variable";
  inline static EntityId kConstantEntityId = "constant";
  inline static EntityId kProcedureEntityId = "procedure";

  inline static std::vector<EntityId> kAllEntityIds{
      kStmtEntityId, kReadEntityId, kPrintEntityId, kCallEntityId, kWhileEntityId, kIfEntityId, kAssignEntityId,
      kVariableEntityId, kConstantEntityId, kProcedureEntityId
  };

  inline static bool const is_entity_id(EntityId const token) {
    return find(kAllEntityIds.begin(), kAllEntityIds.end(), token)
        != kAllEntityIds.end();
  }

  inline static EntityId kModifiesRelId = "Modifies";
  inline static EntityId kPatternRelId = "pattern";

  inline static ClausePtr get_rel_ref(
      EntityId rel_ref_ident, ArgumentPtr arg1, ArgumentPtr arg2) {
    if (rel_ref_ident == kModifiesRelId) {
      return std::make_unique<ModifiesClause>(std::move(arg1), std::move(arg2));
    }
    if (rel_ref_ident == kPatternRelId) {
      return std::make_unique<PatternClause>(std::move(arg1), std::move(arg2));
    }
    throw PqlSyntaxErrorException("Unknown relationship in PQL query");
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
};
}  // namespace qps
