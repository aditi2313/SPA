#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "EntityFactory.h"

namespace qps {

class StmtEntityFactory : public IntEntityFactory {
public:
  StmtEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
      return CreateInstanceList(pkb->get_stmts());
  }

  inline Entity GetAttrValue(const Entity &index,
                             const pkb::PKBReadPtr &pkb) override {
      throw QpsEvaluatorException("Stmt does not have a secondary attr value");
  }
};
}  // namespace qps
