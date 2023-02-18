#pragma once
#include <unordered_set>
namespace pkb {
class ParentData {
 public:
    ParentData(int line, int parent_line);

    inline int get_line() { return line_; }

    inline int get_parent() { return parent_line_; }

    inline void add_to_list(int v) { parents_list.insert(v); }

    inline std::unordered_set<int>& get_parents_list() { return parents_list; }


 private:
    int line_;
    int parent_line_;
    std::unordered_set<int> parents_list;
};
}  // namespace pkb
