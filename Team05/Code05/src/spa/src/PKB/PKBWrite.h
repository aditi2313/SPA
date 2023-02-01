#pragma once

#include "PKB/rows/Modifies.h"

namespace pkb {
class PKBWrite {
 public:
  PKBWrite() {}
  virtual void AddModifies(Modifies) = 0;
};
}
