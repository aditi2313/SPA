#pragma once

namespace pkb {
class FollowsData {
 public:
  FollowsData(int line, int follows);

  inline int get_line() { return line_; }
  inline int get_follows() { return follows_; }

 private:
  int line_;
  int follows_;
};
}  // namespace pkb
