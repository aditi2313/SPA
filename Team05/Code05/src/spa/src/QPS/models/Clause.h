#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include "Argument.h"
#include "PKB/PKBRead.h"
#include "QPS/evaluator/MasterEntityFactory.h"
#include "common/filter/filters/PredicateFilter.h"
#include "QueryResult.h"

namespace qps {
// Pure abstract base class for a Clause:
// It should not be instantiated as its own object.
class Clause {
 public:
  Clause(ArgumentPtr arg1, ArgumentPtr arg2, EntityName LHS, EntityName RHS) :
      arg1_(std::move(arg1)), arg2_(std::move(arg2)), LHS_(LHS), RHS_(RHS) {}
  virtual ~Clause() = 0;

  virtual EntityPtrList Index(
      const EntityPtr &index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) = 0;

  template <class Data>
  static EntityPtrList Index(
      IntEntity *index,
      std::function
          <std::unique_ptr<pkb::IndexableTable<Data>>(int)> pkb_read_function,
      std::function<void(EntityPtrList&, Data)> add_function);

  inline virtual bool ValidateArguments() {
    return ValidateArgumentTypes() && ValidateSynonymTypes();
  }

  inline virtual bool ValidateSynonymTypes() {
    if (arg1_->IsSynonym()) {
      SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg1_.get());
      if (synonym_arg->get_base_entity_name() != LHS_) {
        return false;
      }
    }
    if (arg2_->IsSynonym()) {
      SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg2_.get());
      if (synonym_arg->get_base_entity_name() != RHS_) {
        return false;
      }
    }
    return true;
  }


  virtual bool ValidateArgumentTypes() = 0;

  inline virtual EntityPtrList Filter(
      const EntityPtr &index,
      const EntityPtrList &RHS_filter_values,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) {
    EntityPtrList result;
    for (auto &entity : Index(index, factory, pkb)) {
      for (auto &filter_entity : RHS_filter_values) {
        if (entity->WeakEqual(*filter_entity)) {
          result.push_back(entity->Copy());
        }
      }
    }

    return result;
  }

  inline virtual EntityPtrList SymmetricFilter(
      const EntityPtr &index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) {
    EntityPtrList result;
    for (auto &entity : Index(index, factory, pkb)) {
      if (entity->WeakEqual(*index)) {
        result.push_back(entity->Copy());
      }
    }

    return result;
  }

  bool operator==(Clause const &other) const {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);

    return ti1 == ti2 && *arg1_ == *other.arg1_
        && *arg2_ == *other.arg2_;
  }

  inline bool operator!=(Clause const &other) const {
    return !(*this == other);
  }

  inline ArgumentPtr &get_arg1() { return arg1_; }
  inline ArgumentPtr &get_arg2() { return arg2_; }
  inline EntityName LHS() { return LHS_; }
  inline EntityName RHS() { return RHS_; }

  static std::unique_ptr<Clause> CreateClause(
      EntityName rel_ref_ident, ArgumentPtr arg1, ArgumentPtr arg2);

 protected:
  ArgumentPtr arg1_;
  ArgumentPtr arg2_;
  EntityName LHS_;
  EntityName RHS_;
};

// RS between a Statement/Procedure and a Variable
class ModifiesClause : public Clause {
 public:
  ModifiesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kStmtEntityName, PQL::kVariableEntityName) {}

  EntityPtrList Index(
      const EntityPtr &index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsStmtRef() && arg2_->IsEntRef() && !arg1_->IsWildcard();
  }
};

// RS between statements
class FollowsClause : public Clause {
 public:
  FollowsClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kStmtEntityName, PQL::kStmtEntityName) {}

  EntityPtrList Index(
      const EntityPtr &index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsStmtRef() && arg2_->IsStmtRef();
  }
};

// RS between statements (transitive)
class FollowsTClause : public Clause {
 public:
  FollowsTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kStmtEntityName, PQL::kStmtEntityName) {}

  EntityPtrList Index(
      const EntityPtr &index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsStmtRef() && arg2_->IsStmtRef();
  }
};

class PatternClause : public Clause {
 public:
  PatternClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2),
               PQL::kAssignEntityName, PQL::kAssignEntityName) {}

  EntityPtrList Index(
      const EntityPtr &index,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  EntityPtrList Filter(
      const EntityPtr &index,
      const EntityPtrList &RHS_filter_values,
      const std::unique_ptr<MasterEntityFactory> &factory,
      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateSynonymTypes() override {
    SynonymArg *synonym_arg = dynamic_cast<SynonymArg *>(arg1_.get());
    return synonym_arg->get_entity_name() == LHS_;
  }

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsSynonym();
  }
};
// Relationship between a stmt and a variable or vector of variables
class UsesClause : public Clause {
 public:
  UsesClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2), PQL::kStmtEntityName,
               PQL::kVariableEntityName) {}

  EntityPtrList Index(const EntityPtr &index,
                      const std::unique_ptr<MasterEntityFactory> &factory,
                      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsStmtRef() && arg2_->IsStmtRef() && !arg1_->IsWildcard();;
  }
};
// Relationship between a stmt and another stmt.
class ParentClause : public Clause {
 public:
  ParentClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2), PQL::kStmtEntityName,
               PQL::kStmtEntityName) {}

  EntityPtrList Index(const EntityPtr &index,
                      const std::unique_ptr<MasterEntityFactory> &factory,
                      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsStmtRef() && arg2_->IsStmtRef();
  }
};

class ParentTClause : public Clause {
 public:
  ParentTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2), PQL::kStmtEntityName,
               PQL::kStmtEntityName) {}

  EntityPtrList Index(const EntityPtr &index,
                      const std::unique_ptr<MasterEntityFactory> &factory,
                      const std::unique_ptr<pkb::PKBRead> &pkb) override;

  inline bool ValidateArgumentTypes() override {
    return arg1_->IsStmtRef() && arg2_->IsStmtRef();
  }
};

using ClausePtr = std::unique_ptr<Clause>;

}  // namespace qps
