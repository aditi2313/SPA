#pragma once

#include <unordered_set>

namespace pkb {
class FollowsData {
 public:
  FollowsData(int line, int follows);

  inline int get_line() { return line_; }

  inline int get_follows() { return follows_; }

  inline std::unordered_set<int>& get_follows_list() { return follows_list_; }

  inline void add_to_list(int v) { follows_list_.insert(v); }

 private:
  int line_;
  int follows_;
  std::unordered_set<int> follows_list_;
};
}  // namespace pkb
