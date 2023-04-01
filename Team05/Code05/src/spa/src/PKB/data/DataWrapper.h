#pragma once

#include <cassert>
#include <variant>
#include <string>
#include "DataWrapper.h"
#include "Types.h"

namespace pkb {
class DataWrapper {
 public:
    virtual Key get_key() = 0;
};
}  // namespace pkb
