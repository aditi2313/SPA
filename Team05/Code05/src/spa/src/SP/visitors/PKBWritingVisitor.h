#pragma once

#include <utility>
#include <memory>
#include "TNodeVisitor.h"

namespace sp {
class PKBWritingVisitor : public TNodeVisitor {
 public:
  explicit PKBWritingVisitor(std::unique_ptr<pkb::PKBWrite> pkb_ptr) {
    pkb_ptr_ = std::move(pkb_ptr);
  }

  std::unique_ptr<pkb::PKBWrite> EndVisit() { return std::move(pkb_ptr_); }

 protected:
  std::unique_ptr<pkb::PKBWrite> pkb_ptr_;
};
}  // namespace sp
