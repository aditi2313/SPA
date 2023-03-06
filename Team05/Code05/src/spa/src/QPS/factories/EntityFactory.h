#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>

#include "PKB/PKBRead.h"
#include "common/exceptions/QPSExceptions.h"

using namespace models;  // NOLINT

namespace qps {
class EntityFactory {
 public:
  EntityFactory() {}
  virtual EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) = 0;
  virtual bool is_integer() { return false; }
  virtual bool is_ident() { return false; }

  virtual ~EntityFactory() = default;
};

class IntEntityFactory : public EntityFactory {
 public:
  IntEntityFactory() : EntityFactory() {}

  inline bool is_integer() override {
    return true;
  }

 protected:
  inline EntitySet CreateInstanceList(std::unordered_set<int> ls) {
    EntitySet result;
    for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
      result.insert(Entity(*itr));
    }
    return result;
  }
};

class IdentEntityFactory : public EntityFactory {
 public:
  IdentEntityFactory() : EntityFactory() {}

  inline bool is_ident() override {
    return true;
  }

 protected:
  inline EntitySet CreateInstanceList(std::unordered_set<std::string> ls) {
    EntitySet result;
    for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
      result.insert(Entity(*itr));
    }
    return result;
  }
};

class ProcedureEntityFactory : public IdentEntityFactory {
 public:
  ProcedureEntityFactory() : IdentEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_procedures());
  }
};

class VariableEntityFactory : public IdentEntityFactory {
 public:
  VariableEntityFactory() : IdentEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_variables());
  }
};

class ConstantEntityFactory : public IntEntityFactory {
 public:
  ConstantEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_constants());
  }
};

class StmtEntityFactory : public IntEntityFactory {
 public:
  StmtEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_stmts());
  }
};

class ReadEntityFactory : public IntEntityFactory {
 public:
  ReadEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_read());
  }
};

class PrintEntityFactory : public IntEntityFactory {
 public:
  PrintEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_print());
  }
};

class AssignEntityFactory : public IntEntityFactory {
 public:
  AssignEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_assign());
  }
};

class CallEntityFactory : public IntEntityFactory {
 public:
  CallEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_calls());
  }
};

class WhileEntityFactory : public IntEntityFactory {
 public:
  WhileEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_whiles());
  }
};

class IfEntityFactory : public IntEntityFactory {
 public:
  IfEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_if());
  }
};

using EntityFactoryPtr = std::unique_ptr<EntityFactory>;
}  // namespace qps
