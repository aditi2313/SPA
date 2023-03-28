#pragma once
#include <string>
#include <iostream>
#include <variant>
#include <unordered_set>

#include "Data.h"

namespace pkb {

class UsesData : public Data<std::variant<int, std::string>> {
 public:
  UsesData(std::variant<int, std::string> line,
           const std::unordered_set<std::string>& variable_names);


    friend bool operator<(const UsesData& LHS, const UsesData& RHS) {
        return LHS.line_ < RHS.line_ ||
               (LHS.line_ == RHS.line_ &&
                std::lexicographical_compare(LHS.variable_names_.begin(),
                                             LHS.variable_names_.end(),
                                             RHS.variable_names_.begin(),
                                             RHS.variable_names_.end()));
    }

    friend bool operator==(const UsesData& LHS, const UsesData& RHS) {
        return LHS.line_ == RHS.line_ &&
        LHS.variable_names_ == RHS.variable_names_;
    }

    inline const std::unordered_set<std::string>& get_variables() const {
        return variable_names_;
    }
    inline void add_variables(std::unordered_set<std::string> vars) {
        variable_names_.merge(vars);
    }

 private:
    std::unordered_set<std::string> variable_names_;
};
}  // namespace pkb

