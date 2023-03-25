#include "CallsData.h"

namespace pkb {
pkb::CallsData::CallsData(std::string caller)
    : Data<std::string, std::string>(caller) {}
}  // namespace pkb
