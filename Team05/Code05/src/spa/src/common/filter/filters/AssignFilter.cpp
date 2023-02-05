#include "AssignFilter.h"

#include <memory>
#include <string>
#include <utility>

#include "ModifiesFilter.h"
#include "PKB/tables/IndexableTable.h"

namespace filter {

AssignTablePtr AssignFilterByVariable::FilterTable(AssignTablePtr assign) {
  AssignTablePtr result = std::make_unique<pkb::AssignTable>();

  for (int line : assign->get_indexes()) {
    auto assign_data = assign->get_row(line);
    std::string name = assign_data->get_variable();
    if (variable_ == name) {
      result->add_row(line, assign_data);
      break;
    }
  }

  return std::move(result);
}

AssignTablePtr AssignFilterByExpression::FilterTable(AssignTablePtr assign) {
  AssignTablePtr result = std::make_unique<pkb::AssignTable>();

  for (int line : assign->get_indexes()) {
    auto assign_data = assign->get_row(line);
    if (assign_data->TestExpression(expr_->Copy())) {
      result->add_row(line, assign_data);
    }
  }

  return std::move(result);
}
}  // namespace filter
