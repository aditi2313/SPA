#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "common/filter/filters/ModifiesFilter.h"
#include "models/results/QueryResult.h"
#include "PKBRelationTable.h"

typedef std::unique_ptr<filter::ModifiesFilter> ModifiesFilterPtr;

namespace pkb {
class PKBRead {
 public:
   explicit PKBRead(std::unique_ptr<PKBRelationTable>& relation_table) {
    relation_table_ = std::move(relation_table);
  }
  models::QueryResult Modifies(ModifiesFilterPtr&);

 private:
  std::unique_ptr<PKBRelationTable> relation_table_;
};


}  // namespace pkb
