#pragma once

#include "PKB/rows/Modifies.h"

namespace pkb {
class PKBWrite {
 public:
  PKBWrite() {}
  void addModifies(Modiifes) = 0;  
};
}