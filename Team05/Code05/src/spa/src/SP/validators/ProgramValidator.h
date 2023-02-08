#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <string>

#include "models/AST/ProgramNode.h"
#include "Validator.h"

namespace sp {
class ProgramValidator : public Validator {
 public:
    explicit ProgramValidator(std::unique_ptr<ast::ProgramNode> &root)
        : root_(root) { }

    bool Validate() override;

 private:
    std::vector<std::string> procedure_names_;
    std::unique_ptr<ast::ProgramNode> &root_;
};
}  // namespace sp
