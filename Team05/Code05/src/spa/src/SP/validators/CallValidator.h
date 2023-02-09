#pragma once

#include <utility>
#include <vector>
#include <string>

#include "Validator.h"

namespace sp {

class CallValidator : public Validator {
 public:
    CallValidator(std::vector<std::string> procedure_names,
                  std::vector<std::string> call_names)
                  : procedure_names_(std::move(procedure_names))
                  , call_names_(std::move(call_names)) { }

    bool Validate() override;
 private:
    std::vector<std::string> procedure_names_;
    std::vector<std::string> call_names_;

    bool ValidateProcedureNameExists();
};

}  // namespace sp
