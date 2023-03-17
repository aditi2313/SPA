#pragma once

namespace qps {
enum class ClauseType {
  kAffects,
  kModifies,
  kFollows,
  kFollowsT,
  kParent,
  kParentT,
  kUses,
  kCalls,
  kCallsT,
  kNext,
  kWith,
  kPatternAssign,
  kPatternIf,
  kPatternWhile,
  kPatternUndetermined
};
}  // namespace qps
