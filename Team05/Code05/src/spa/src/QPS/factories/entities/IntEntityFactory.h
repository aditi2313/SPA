#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class IntEntityFactory : public EntityFactory {
public:
  IntEntityFactory() : EntityFactory() {}

  inline bool is_integer() override { return true; }

protected:
  inline EntitySet CreateInstanceList(std::unordered_set<int> ls) {
      EntitySet result;
      for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
          result.insert(Entity(*itr));
      }
      return result;
  }
};
}  // namespace qps
