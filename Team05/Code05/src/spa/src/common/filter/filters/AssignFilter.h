#pragma once

#include <memory>

#include "IndexableFilter.h"
#include "PKB/data/AssignData.h"

namespace filter {
typedef std::shared_ptr<pkb::AssignData> AssignDataPtr;
class AssignFilterAll : public IndexableFilter<AssignDataPtr> {
 public:
  // Filter for testing
  virtual pkb::IndexableTablePtr<AssignDataPtr> FilterTable(
      pkb::IndexableTablePtr<AssignDataPtr> t) {
    return t->copy();
  }
};

}  // namespace filter
