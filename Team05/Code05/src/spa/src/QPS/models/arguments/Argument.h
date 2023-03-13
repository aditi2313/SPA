#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/models/Table.h"
#include "QPS/models/Synonym.h"
#include "QPS/factories/MasterEntityFactory.h"
#include "models/types.h"

namespace qps {
extern MasterEntityFactory master_entity_factory_;

// An argument for a clause.
// e.g. Clause(Argument, Argument)
// It can be a synonym for statement, procedure, variable,
// character strings, wildcard, or expressions for exact/partial matches
class Argument {
 public:
  // synonym | _ | INTEGER
  virtual bool IsStmtRef() { return false; }
  // synonym | _ | "ident"
  virtual bool IsEntRef() { return false; }
  virtual bool IsWildcard() { return false; }
  virtual bool IsSynonym() { return false; }
  virtual bool IsExpression() { return false; }

  // IdentArg and IntegerArg are IdentType and IntegerType
  // respectively.
  // SynonymArg can also be either IdentType or IntegerType
  // depending on which entity it represents.
  virtual bool IsIdentType() { return false; }
  virtual bool IsIntegerType() { return false; }

  virtual bool operator==(Argument &other) = 0;

  virtual std::unique_ptr<Argument> Copy() = 0;

  // Returns true if the entity name of the argument
  // exists in the parameter hashset of entity names
  virtual bool Validate(
      std::unordered_set<EntityName> &entity_names) = 0;

  virtual void InitializeEntities(
      Table &table, pkb::PKBReadPtr &pkb, EntitySet &result) = 0;

  inline virtual std::ostream &dump(std::ostream &str) const {
    return str << "Argument";
  }

  friend inline std::ostream &operator<<(std::ostream &o, Argument &base) {
    return base.dump(o);
  }

  virtual ~Argument() = default;
};

using ArgumentPtr = std::unique_ptr<Argument>;
}  // namespace qps
