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
  virtual EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) = 0;
  virtual Entity GetAttrValue(
      const Entity &index, const pkb::PKBReadPtr &pkb) = 0;

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

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_procedures());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on a procedure");
  }
};

class VariableEntityFactory : public IdentEntityFactory {
 public:
  VariableEntityFactory() : IdentEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_variables());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on a variable");
  }
};

class ConstantEntityFactory : public IntEntityFactory {
 public:
  ConstantEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_constants());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on a constant");
  }
};

class StmtEntityFactory : public IntEntityFactory {
 public:
  StmtEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_stmts());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on a stmt");
  }
};

class ReadEntityFactory : public IntEntityFactory {
 public:
  ReadEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_read());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    return Entity(pkb->get_var_name_from_line(index.get_int()));
  }
};

class PrintEntityFactory : public IntEntityFactory {
 public:
  PrintEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_print());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    return Entity(pkb->get_var_name_from_line(index.get_int()));
  }
};

class AssignEntityFactory : public IntEntityFactory {
 public:
  AssignEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_assign());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on an assign");
  }
};

class CallEntityFactory : public IntEntityFactory {
 public:
  CallEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_calls());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    return Entity(pkb->get_proc_name_from_line(index.get_int()));
  }
};

class WhileEntityFactory : public IntEntityFactory {
 public:
  WhileEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_whiles());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on a while");
  }
};

class IfEntityFactory : public IntEntityFactory {
 public:
  IfEntityFactory() : IntEntityFactory() {}

  inline EntitySet GetAllFromPKB(const pkb::PKBReadPtr &pkb) override {
    return CreateInstanceList(pkb->get_if());
  }

  inline Entity GetAttrValue(const Entity &index, const pkb::PKBReadPtr &pkb) override {
    throw QpsEvaluatorException(
        "Tried to get attrValue on an if");
  }
};

using EntityFactoryPtr = std::unique_ptr<EntityFactory>;
}  // namespace qps
