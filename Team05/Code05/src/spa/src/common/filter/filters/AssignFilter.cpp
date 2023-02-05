#include "ModifiesFilter.h"

#include <memory>
#include <string>
#include <utility>

#include "PKB/tables/IndexableTable.h"
#include "AssignFilter.h"


namespace filter {

    AssignTablePtr filter::AssignFilterByVariable::FilterTable(AssignTablePtr assign) {
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
}  // namespace filter
