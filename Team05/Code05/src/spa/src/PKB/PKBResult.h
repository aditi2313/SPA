#pragma once

#include <memory>
#include <utility>

#include "PKBRelationTable.h"

namespace pkb {
template <typename T>
class PKBResult {
 public:
  PKBResult(std::unique_ptr<PKBRelationTable> table,
            std::unique_ptr<T> result) {
    table_ = std::move(table);
    result_ = std::move(result);
  }

  inline std::unique_ptr<PKBRelationTable> get_table() { return std::move(table_);
  }
  inline std::unique_ptr<T> get_result() { return std::move(result_);
  }

 private:
  std::unique_ptr<PKBRelationTable> table_;
  std::unique_ptr<T> result_;
};

}  // namespace pkb
