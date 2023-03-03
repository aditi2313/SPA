#pragma once

#include <memory>
#include <utility>

#include "SP/PKBWriter.h"
#include "TNodeVisitor.h"

namespace sp {
class PKBWritingVisitor : public TNodeVisitor, public PKBWriter {};
}  // namespace sp
