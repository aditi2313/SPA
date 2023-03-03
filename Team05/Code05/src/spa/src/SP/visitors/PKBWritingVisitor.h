#pragma once

#include <memory>
#include <utility>

#include "SP/PKBWriter.h"
#include "TNodeVisitor.h"

namespace sp {
class PKBWritingVisitor : public TNodeVisitor, public PKBWriter {
 public:
  explicit PKBWritingVisitor(std::unique_ptr<pkb::PKBWrite> pkb_ptr)
      : PKBWriter(std::move(pkb_ptr)) {}
};
}  // namespace sp
