#pragma once

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>

#include "models/EntityExport.h"
#include "PKB/PKBRead.h"
#include "common/Exceptions.h"

using namespace models;  // NOLINT

namespace qps {
using PKBPtr = std::unique_ptr<pkb::PKBRead>;

class EntityFactory {
 public:
  EntityFactory() {}
  virtual EntityPtrList GetAllFromPKB(PKBPtr &pkb) = 0;
  virtual EntityPtr CreateInstance(std::string ident) = 0;
  virtual EntityPtr CreateInstance(int number) = 0;

  virtual ~EntityFactory() = 0;
};

class IntEntityFactory : public EntityFactory {
 public:
  IntEntityFactory() : EntityFactory() {}

 protected:
  inline EntityPtrList CreateInstanceList(std::unordered_set<int> ls) {
    EntityPtrList result;
    for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
      result.push_back(CreateInstance(*itr));
    }
    return result;
  }
};

class IdentEntityFactory : public EntityFactory {
 public:
  IdentEntityFactory() : EntityFactory() {}

 protected:
  inline EntityPtrList CreateInstanceList(std::unordered_set<std::string> ls) {
    EntityPtrList result;
    for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
      result.push_back(CreateInstance(*itr));
    }
    return result;
  }
};

class ProcedureEntityFactory : public IdentEntityFactory {
 public:
  ProcedureEntityFactory() : IdentEntityFactory() {}
  inline EntityPtr CreateInstance(std::string ident) override {
    return std::make_unique<Procedure>(ident);
  }
  inline EntityPtr CreateInstance(int number) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_procedures());
  }
};

class VariableEntityFactory : public IdentEntityFactory {
 public:
  VariableEntityFactory() : IdentEntityFactory() {}
  inline EntityPtr CreateInstance(std::string ident) override {
    return std::make_unique<Variable>(ident);
  }
  inline EntityPtr CreateInstance(int number) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_variables());
  }
};

class ConstantEntityFactory : public IntEntityFactory {
 public:
  ConstantEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<Constant>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_constants());
  }
};

class StmtEntityFactory : public IntEntityFactory {
 public:
  StmtEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<Stmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_stmts());
  }
};

class ReadEntityFactory : public IntEntityFactory {
 public:
  ReadEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<ReadStmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_read());
  }
};

class PrintEntityFactory : public IntEntityFactory {
 public:
  PrintEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<PrintStmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_print());
  }
};

class AssignEntityFactory : public IntEntityFactory {
 public:
  AssignEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<AssignStmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_assign());
  }
};

class CallEntityFactory : public IntEntityFactory {
 public:
  CallEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<CallStmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_calls());
  }
};

class WhileEntityFactory : public IntEntityFactory {
 public:
  WhileEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<CallStmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_whiles());
  }
};

class IfEntityFactory : public IntEntityFactory {
 public:
  IfEntityFactory() : IntEntityFactory() {}
  inline EntityPtr CreateInstance(int number) override {
    return std::make_unique<IfStmt>(number);
  }
  inline EntityPtr CreateInstance(std::string ident) override {
    throw NotImplementedException();
  }
  inline EntityPtrList GetAllFromPKB(PKBPtr &pkb) override {
    return CreateInstanceList(pkb->get_if());
  }
};

using EntityFactoryPtr = std::unique_ptr<EntityFactory>;
}  // namespace qps
