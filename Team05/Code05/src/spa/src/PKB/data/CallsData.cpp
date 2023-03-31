#include "CallsData.h"

namespace pkb {
pkb::CallsData::CallsData(Proc caller)
    : Data<Proc, Proc>(caller) {}
}  // namespace pkb
