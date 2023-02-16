#pragma once

namespace pkb {
class ParentData {
 public:
    ParentData(int line, int parent_line);

    inline int get_line() { return line_; }

    inline int get_parent() { return parent_line_; }

 private:
    int line_;
    int parent_line_;
};
}  // namespace pkb
