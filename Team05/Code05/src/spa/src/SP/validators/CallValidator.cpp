#include "CallValidator.h"
#include <unordered_set>

namespace sp {
    bool CallValidator::Validate() {
        return ValidateProcedureNameExists();
    }

    bool CallValidator::ValidateProcedureNameExists() {
        std::unordered_set<std::string> procedure_names_set;
        for (auto &procedure_name : procedure_names_) {
            procedure_names_set.insert(procedure_name);
        }

        for (auto &call_name : call_names_) {
            if (!procedure_names_set.count(call_name)) {
                return false;
            }
        }

        return true;
    }
}  // namespace sp
