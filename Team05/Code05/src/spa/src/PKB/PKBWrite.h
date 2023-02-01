#pragma once

#include "PKB/rows/Modifies.h"

namespace pkb {
class PKBWrite {
 public:
  PKBWrite() {}
  virtual void addModifies(Modifies) = 0;
};
}
