#pragma once
#include <string>
#include <vector>

namespace pkb {

class UsesData {
 public:
    UsesData(int line, const std::vector<std::string>& variable_names);

    inline int get_line() { return line_; }

    inline const std::vector<std::string>& get_variables() {
        return variable_names_;
    }

 private:
    int line_;
    std::vector<std::string> variable_names_;
};
}  // namespace pkb
