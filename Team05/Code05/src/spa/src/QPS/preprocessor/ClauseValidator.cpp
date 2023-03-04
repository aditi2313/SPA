#include "ClauseValidator.h"

#include <iostream>

namespace qps {
void ClauseValidator::ValidateClauseArgumentTypes(
    PQL::RelName rel_name, ArgumentPtr &arg1, ArgumentPtr &arg2) {
  if (rel_name == PQL::kModifiesRelName) {
    if (!(arg1->IsStmtRef() && arg2->IsEntRef()))
      ThrowException(rel_name);
    return;
  }

  if (rel_name == PQL::kPatternRelName) {
    if (!(arg1->IsSynonym()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kFollowsRelName) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }

  if (rel_name == PQL::kFollowsTRelName) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kParentRelName) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kParentTRelName) {
    if (!(arg1->IsStmtRef() && arg2->IsStmtRef()))
      ThrowException(rel_name);
    return;
  }
  if (rel_name == PQL::kUsesRelName) {
    if (!(arg1->IsStmtRef() && arg2->IsEntRef()))
      ThrowException(rel_name);
    return;
  }

  throw PqlSyntaxErrorException("Unknown relationship in PQL query");
}
}  // namespace qps
