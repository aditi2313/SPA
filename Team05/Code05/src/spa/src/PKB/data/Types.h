#pragma once

#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <variant>
#include <string>

namespace pkb {
    typedef std::unordered_set<std::string> ProcSet;
    typedef std::unordered_set<std::string> VarSet;
    typedef std::unordered_set<int> LineSet;
    typedef std::variant<int, std::string> Key;
    typedef std::unordered_map<int, std::string> LineToVarSet;
    typedef std::unordered_map<int, std::string> LineToProcSet;
    typedef int Line;
    typedef std::string Var;
    typedef std::string Proc;
}  // namespace pkb
