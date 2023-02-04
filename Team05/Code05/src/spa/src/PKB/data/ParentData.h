#pragma once

class ParentData {
 public:
  ParentData(int line, int parent_line)
      : line_(line), parent_line_(parent_line) {}
  int get_line() { return line_; }
  int get_parent() { return parent_line_; }

 private:
  int line_;
  int parent_line_;
};