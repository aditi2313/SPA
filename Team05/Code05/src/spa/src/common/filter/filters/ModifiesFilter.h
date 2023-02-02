#pragma once

#include <vector>

#include "Filter.h"
#include "common/Exceptions.h"
#include "models/pkb/Modifies.h"

namespace filter {

class ModifiesFilter : public Filter<models::Modifies> {
 public:
  ModifiesFilter() {}
  inline std::vector<models::Modifies> FilterTable(
      const std::vector<models::Modifies>& modifies) {
    throw new NotImplementedException();
  }

 private:
};

}  // namespace filter
