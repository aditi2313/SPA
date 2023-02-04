#pragma once

namespace pkb {
class FollowData {
 public:
  FollowData(int line, int follows) : line_(line), follows_(follows) {}

  int get_line() { return line_; }
  int get_follows() { return follows_; }

 private:
  int line_;
  int follows_;
};
}  // namespace pkb
