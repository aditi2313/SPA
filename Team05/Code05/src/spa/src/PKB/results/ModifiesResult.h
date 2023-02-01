#pragma once

#include <vector>

#include "PKB/rows/Modifies.h"

class ModifiesResult {
 public:
  std::vector<Modifies> getResult() = 0;
  bool isError() = 0;

  /// <summary>
  /// Joins the two Modifies results together
  ///
  /// </summary>
  /// <param name=""></param>
  /// <returns></returns>
  ModifiesResult join(ModifiesResult) = 0;
};
