#pragma once

#include <cassert>
#include <variant>
#include <string>
#include "DataWrapper.h"

namespace pkb {
class DataWrapper {
 public:
    virtual std::variant<int, std::string> get_key() = 0;
};
}  // namespace pkb
