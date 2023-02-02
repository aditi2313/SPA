#include <memory>

#include "QueryResult.h"
#include "PKB/data/ModifiesData.h"

using pkb::ModifiesData;
using std::unique_ptr;
using std::make_unique;

namespace models {
class ModifiesResult : public QueryResult {

 public:
   void add_modifies(ModifiesData &data) { 
     auto result = make_unique<ModifiesData>(data.get_line(), data.get_variables());
     add_query_result(data);
   }
};
}
