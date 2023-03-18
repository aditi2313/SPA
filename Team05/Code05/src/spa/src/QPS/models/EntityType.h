#pragma once

namespace qps {
enum class EntityType {
  kProcedure,
  kStmt,
  kRead,
  kPrint,
  kAssign,
  kCall,
  kWhile,
  kIf,
  kVariable,
  kConstant,
  // Used when creating synonym arguments
  // without knowing its entity type
  kUndetermined
};
}  // namespace qps
