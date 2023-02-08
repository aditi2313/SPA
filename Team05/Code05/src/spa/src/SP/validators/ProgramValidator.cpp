#include "ProgramValidator.h"
#include "ProcedureValidator.h"

namespace sp {
    bool ProgramValidator::Validate() {
        for (auto &child : root_->get_children()) {
            procedure_names_.push_back(child->get_name());
        }

        auto procedure_validator = sp::ProcedureValidator(procedure_names_);
        return procedure_validator.Validate();
    }
}  // namespace sp
