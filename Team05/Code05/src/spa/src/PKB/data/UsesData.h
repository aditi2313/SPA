#pragma once
#include <string>
#include <unordered_set>

namespace pkb {

class UsesData {
 public:
    UsesData(int line, const std::unordered_set<std::string>& variable_names);

    inline int get_line() { return line_; }

    inline const std::unordered_set<std::string>& get_variables() {
        return variable_names_;
    }

 private:
    int line_;
    std::unordered_set<std::string> variable_names_;
};
}  // namespace pkb
