#pragma once

#include <cassert>
#include <unordered_set>
#include <variant>
#include <string>

namespace pkb {
    typedef std::unordered_set<std::string> ProcSet;
    typedef std::unordered_set<std::string> VarSet;
    typedef std::unordered_set<int> LineSet;
    typedef std::variant<int, std::string> Key;
}  // namespace pkb
