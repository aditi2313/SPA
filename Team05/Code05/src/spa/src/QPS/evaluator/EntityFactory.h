#pragma once

#include "models/EntityExport.h"
#include "PKB/PKBRead.h"

using namespace models;  // NOLINT

namespace qps {
using PKBPtr = std::unique_ptr<pkb::PKBRead>;
using EntityPtrList = std::vector<EntityPtr>;

class EntityFactory {
 public:
  EntityFactory() {}
  virtual EntityPtrList GetAllFromPKB(PKBPtr &pkb) = 0;
  virtual EntityPtr CreateInstance(int number) = 0;
  virtual EntityPtr CreateInstance(std::string ident) = 0;

  virtual ~EntityFactory() = 0;
 protected:
  inline EntityPtrList CreateInstanceList(std::unordered_set<std::string> ls) {
    EntityPtrList result;
    for (auto itr = ls.begin(); itr != ls.end(); ++itr) {
      result.push_back(CreateInstance(*itr));
    }
    return result;
  }
};

class IntEntityFactory : public EntityFactory {
 public:
  IntEntityFactory() : EntityFactory() {}
};

class IdentEntityFactory : public EntityFactory {
 public:
  IdentEntityFactory() : EntityFactory() {}
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
    auto pkb_results = pkb->get_variables();
    EntityPtrList result;
    for (auto itr = pkb_results.begin(); itr != pkb_results.end(); ++itr) {
      result.push_back(CreateInstance(*itr));
    }
    return result;
  }
};

using EntityFactoryPtr = std::unique_ptr<EntityFactory>;

}