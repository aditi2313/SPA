#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

namespace sp {

class TopologicalSorter {
 public:
  static std::vector<std::string> Sort(
       std::unordered_map<std::string, std::unordered_set<std::string>>
           & called_by);
};

}  // namespace sp
