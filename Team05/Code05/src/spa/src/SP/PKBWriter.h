#pragma once

#include <memory>
#include <utility>

#include "PKB/PKBWrite.h"

namespace sp {

class PKBWriter {
 public:
  explicit PKBWriter(std::unique_ptr<pkb::PKBWrite> pkb_ptr) {
    pkb_ptr_ = std::move(pkb_ptr);
  }

  std::unique_ptr<pkb::PKBWrite> EndVisit() { return std::move(pkb_ptr_); }

 protected:
  std::unique_ptr<pkb::PKBWrite> pkb_ptr_;
};

}  // namespace sp
