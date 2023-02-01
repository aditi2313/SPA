#pragma once

#include <memory>

#include "PKBRelationTable.h"
#include "common/stub/ModifiesStub.h"
#include "common/stub/ParentStub.h"

namespace pkb {
class PKBWrite {
 public:
  explicit PKBWrite(
      std::shared_ptr<PKBRelationTable> other_pkb_relation_table) {
    this->pkb_relation_table = other_pkb_relation_table;
  }
  void AddModifies(stub::ModifiesStub);
  void AddParent(stub::ParentStub);

 private:
  // todo: think of alternatives to the use of shared pointer.
  // Currently this shared pointer has to be used simply
  // because the relation table has to be shared by both
  // PKBWrite as well as PKBRead.
  std::shared_ptr<PKBRelationTable> pkb_relation_table;
};
}  // namespace pkb
