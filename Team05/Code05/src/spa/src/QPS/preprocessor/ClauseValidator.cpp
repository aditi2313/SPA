#include "ClauseValidator.h"

#include <iostream>

namespace qps {
void ClauseValidator::ValidateClauseArgumentTypes(
    PQL::RelName rel_name, ArgumentPtr &arg1, ArgumentPtr &arg2) {
  if (rel_name == PQL::kModifiesRelId) {
    if (!(arg1->IsStmtRef() && arg2->IsEntRef()))
      ThrowException(rel_name);
    return;
  }

  if (rel_name == PQL::kPatternRelId) {
    if (!(arg1->IsSynonym()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kFollowsRelId) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }

  if (rel_name == PQL::kFollowsTRelId) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kParentRelId) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kParentTRelId) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kUsesRelId) {
    if (!(arg1->IsStmtRef() && arg2->IsEntRef()))
      ThrowException(rel_name);
    return;
  }

  throw PqlSyntaxErrorException("Unknown relationship in PQL query");
}
}  // namespace qps
