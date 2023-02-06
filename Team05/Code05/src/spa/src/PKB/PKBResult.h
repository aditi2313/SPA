#pragma once

#include <memory>
#include <utility>

#include "PKBRelationTable.h"

namespace pkb {
template <typename T>
class PKBResult {
 public:
  explicit PKBResult(std::unique_ptr<T> result) { result_ = std::move(result); }

  inline std::unique_ptr<T> get_result() { return std::move(result_); }

 private:
  std::unique_ptr<T> result_;
};

}  // namespace pkb
