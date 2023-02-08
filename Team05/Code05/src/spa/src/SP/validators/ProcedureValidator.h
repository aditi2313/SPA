#pragma once

#include <vector>
#include <string>

#include "Validator.h"

namespace sp {
class ProcedureValidator : public Validator {
 public:
    explicit ProcedureValidator(std::vector<std::string> proc_names);

    bool Validate() override;

 private:
    std::vector<std::string> proc_names_;

    bool ValidateNoDuplicateProcedureNames();
};
}  // namespace sp
