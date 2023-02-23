#pragma once

#include "Synonym.h"

namespace qps {
class Table {
 public:
  // Methods to create:
  // CrossProduct
  // Join
  // Select

 private:
  std::vector<Synonym> columns_;
  std::vector<EntityPtrList> data_;
};
}  // namespace qps