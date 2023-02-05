#include "ModifiesFilter.h"

#include <memory>
#include <string>
#include <utility>

#include "PKB/tables/IndexableTable.h"

namespace filter {
ModifiesTablePtr ModifiesFilterByVariable::FilterTable(
    ModifiesTablePtr modifies) {
  ModifiesTablePtr result = std::make_unique<pkb::ModifiesTable>();

  for (int line : modifies->get_indexes()) {
    auto modifies_data = modifies->get_row(line);
    for (std::string name : modifies_data.get_variables()) {
      if (variables_.find(name) != variables_.end()) {
        result->add_row(line, modifies_data);
        break;
      }
    }
  }
  return std::move(result);
}

//template<>
//ModifiesFilter::~IndexableFilter() = default;
//ModifiesFilterByLine::~ModifiesFilterByLine() = default;

}  // namespace filter
