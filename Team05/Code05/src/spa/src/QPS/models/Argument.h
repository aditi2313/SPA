#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

#include "QPS/models/PQL.h"
#include "QPS/models/Table.h"
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

  virtual ~Argument() = 0;
  inline virtual std::ostream &dump(std::ostream &str) const {
    return str << "Argument";
  }

  friend inline std::ostream &operator<<(std::ostream &o, Argument &base) {
    return base.dump(o);
  }
};

using ArgumentPtr = std::unique_ptr<Argument>;

class Wildcard : public Argument {
 public:
  Wildcard() : Argument() {}

  inline bool IsWildcard() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline std::ostream &dump(std::ostream &str) const override {
    return str << "Wildcard";
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<Wildcard>(*this);
  }

  inline void set_entity_name(EntityName entity_name) {
    entity_name_ = entity_name;
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    return ti1 == ti2;
  }

  inline bool Validate(
      std::unordered_set<EntityName> &entity_names) override {
    return true;
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    if (entity_name_.empty()) return;
    results = master_entity_factory_.GetAllFromPKB(
        entity_name_, pkb);
  }

 private:
  EntityName entity_name_;
};

class SynonymArg : public Argument {
 public:
  explicit SynonymArg(SynonymName syn_name)
      : Argument(), syn_name_(syn_name) {}

  inline bool IsSynonym() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline bool IsIdentType() override {
    if (entity_name_.empty()) return false;
    if (!attr_name_.empty())
      return PQL::is_attr_name_ident(attr_name_);
    return master_entity_factory_.is_ident(entity_name_);
  }

  inline bool IsIntegerType() override {
    if (entity_name_.empty()) return false;
    if (!attr_name_.empty())
      return PQL::is_attr_name_integer(attr_name_);
    return master_entity_factory_.is_integer(entity_name_);
  }

  inline SynonymName get_syn_name() { return syn_name_; }
  inline SynonymName get_full_name() {
    if (attr_name_.empty()) return syn_name_;
    return PQL::join_attr_ref(syn_name_, attr_name_);
  }

  inline void set_entity_name(EntityName entity_name) {
    entity_name_ = entity_name;
  }

  inline void set_attr_name(AttrName attr_name) {
    attr_name_ = attr_name;
  }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Synonym: " << syn_name_ << "->" << entity_name_
        << (attr_name_.empty() ? "" : " with: " + attr_name_);
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<SynonymArg>(*this);
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    auto arg = dynamic_cast<SynonymArg *>(&other);
    return syn_name_ == arg->syn_name_
        && entity_name_ == arg->entity_name_;
  }

  static inline SynonymName get_full_name(ArgumentPtr &arg) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
    return syn_arg->get_full_name();
  }

  inline bool Validate(
      std::unordered_set<EntityName> &entity_names) override {
    // Synonym has not been declared
    if (entity_name_.empty()) return false;
    if (!attr_name_.empty()) {
      // This is an attrRef: e.g s.stmt#
      // Validate if the synonym type matches the attrName
      // e.g s must match with stmt#
      return PQL::ValidateAttrRef(
          attr_name_, entity_name_);
    }
    // Else just verify that the synonym type matches the
    // context of the clause, e.g Modifies(stmt, var)
    return entity_names.count(entity_name_);
  }

  inline bool is_secondary_attr_ref() {
    return !attr_name_.empty()
        && PQL::is_attr_ref_secondary(entity_name_, attr_name_);
  }

  inline Entity get_secondary_attr_value(
      const pkb::PKBReadPtr &pkb, const Entity &index
  ) {
    return master_entity_factory_.GetAttrValue(entity_name_, index, pkb);
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    InitializeEntities(
        table, pkb, results, this->is_secondary_attr_ref());
  }

  inline void InitializeEntities(
      Table &table,
      const pkb::PKBReadPtr &pkb,
      EntitySet &results,
      bool is_attr_ref) {
    EntitySet indexes;

    if (table.HasColumn(syn_name_)) {
      std::vector<std::vector<Entity>> values;
      table.Select({syn_name_}, values);
      for (auto &entities : values) {
        indexes.insert(entities.at(0));
      }
    } else {
      indexes = master_entity_factory_.GetAllFromPKB(
          entity_name_, pkb);
    }

    for (auto &index : indexes) {
      if (is_attr_ref) {
        results.insert(get_secondary_attr_value(pkb, index));
      } else {
        results.insert(index);
      }
    }
  }

  void UpdateTableWithAttrValue(
      const pkb::PKBReadPtr &pkb,
      Table &query_table);

 private:
  SynonymName syn_name_;
  EntityName entity_name_;
  AttrName attr_name_;
};

class IdentArg : public Argument {
 public:
  explicit IdentArg(std::string ident) : Argument(), ident_(ident) {}

  inline bool IsEntRef() override { return true; }
  inline bool IsIdentType() override { return true; }

  inline std::string get_ident() { return ident_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Ident Arg: " << ident_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<IdentArg>(*this);
  }
  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    auto arg = dynamic_cast<IdentArg *>(&other);
    return ident_ == arg->ident_;
  }

  inline bool Validate(
      std::unordered_set<EntityName> &entity_names) override {
    for (auto &entity_name : entity_names) {
      if (master_entity_factory_.is_ident(entity_name)) {
        return true;
      }
    }
    return false;
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    results.insert(Entity(ident_));
  }

 private:
  std::string ident_;
};

class IntegerArg : public Argument {
 public:
  explicit IntegerArg(int number) : Argument(), number_(number) {}

  inline bool IsStmtRef() override { return true; }
  inline bool IsIntegerType() override { return true; }

  inline int get_number() { return number_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Int Arg: " << number_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<IntegerArg>(*this);
  }
  inline bool Validate(
      std::unordered_set<EntityName> &entity_names) override {
    for (auto &entity_name : entity_names) {
      if (master_entity_factory_.is_integer(entity_name)) {
        return true;
      }
    }
    return false;
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    results.insert(Entity(number_));
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    auto arg = dynamic_cast<IntegerArg *>(&other);
    return number_ == arg->number_;
  }

 private:
  int number_;
};

class ExpressionArg : public Argument {
 public:
  explicit ExpressionArg(sp::ExprNodePtr expr, bool is_exact)
      : Argument(), expr_(std::move(expr)), is_exact_(is_exact) {}

  inline bool IsExpression() override { return true; }
  inline sp::ExprNodePtr &get_expression() { return expr_; }
  inline bool is_exact() { return is_exact_; }
  inline std::ostream &dump(std::ostream &str) const override {
    str << "Expr Arg: " << expr_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<ExpressionArg>(
        expr_->Copy(), is_exact_);
  }

  inline bool Validate(
      std::unordered_set<EntityName> &entity_names) override {
    return true;
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    return;
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    auto arg = dynamic_cast<ExpressionArg *>(&other);
    return expr_->DeepEquals(*(arg->expr_))
        && is_exact_ == arg->is_exact_;
  }

 private:
  sp::ExprNodePtr expr_;  // Expression
  bool is_exact_;
};

}  // namespace qps
