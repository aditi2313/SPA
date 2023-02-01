#pragma once

#include <vector>

#include "PKB/rows/Modifies.h"

class ModifiesResult {
 public:
  std::vector<Modifies> getResult() = 0;
  bool isError() = 0;

  /// <summary>
  /// Joins the two Modifies results together
  /// TODO: sync with #13
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  ModifiesResult IntersectWith(ModifiesResult) = 0;
};
