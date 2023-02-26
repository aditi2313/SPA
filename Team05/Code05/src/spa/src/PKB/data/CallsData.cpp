#include "CallsData.h"

namespace pkb {
    pkb::CallsData::CallsData(std::string caller, std::string callee)
            : caller_(caller), callee_(callee) {
        callee_list_.insert(callee);
    }
}  // namespace pkb
