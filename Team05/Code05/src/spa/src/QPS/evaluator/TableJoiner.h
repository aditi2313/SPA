#pragma once

#include "QPS/models/Table.h"

namespace qps {
class TableJoiner {
 public:
  static Table Join(Table LHS, Table RHS);

};
}   // namespace qps


