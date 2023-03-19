#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class IdentEntityFactory : public EntityFactory {
public:
  IdentEntityFactory() : EntityFactory() {}

  inline bool is_ident() override { return true; }

protected:
  inline EntitySet CreateInstanceList(std::unordered_set<std::string> ls) {
      EntitySet result;
      for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
          result.insert(Entity(*itr));
      }
      return result;
  }
};

}  // namespace qps
