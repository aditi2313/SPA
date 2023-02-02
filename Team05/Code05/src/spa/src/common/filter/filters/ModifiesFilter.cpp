#include <memory>

#include "ModifiesFilter.h"

namespace filter {
ModifiesTablePtr ModifiesFilterByVariable::FilterTable(
    ModifiesTablePtr modifies) {
  ModifiesTablePtr result = std::make_unique<ModifiesTable>();

  for (int id : modifies->get_rows()) {
    auto modify_data = modifies->get_row(id);
    for (std::string name : modify_data.get_variables()) {
      if (variables_.find(name) != variables_.end()) {
        result->add_row(id, modify_data);
        break;
      }
    }
  }
  return std::move(result);
}
}  // namespace filter