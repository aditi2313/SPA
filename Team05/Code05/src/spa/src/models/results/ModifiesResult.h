#include <memory>

#include "PKB/data/ModifiesData.h"
#include "QueryResult.h"

using pkb::ModifiesData;
using std::make_unique;
using std::unique_ptr;

namespace models {
class ModifiesResult : public QueryResult {
 public:
  void add_modifies(const ModifiesData &data) {
    auto result =
        make_unique<ModifiesData>(data.get_line(), data.get_variables());
    add_query_result(data);
  }
};
}  // namespace models
