#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

#include "Argument.h"

namespace qps {

class SynonymArg : public Argument {
 public:
  explicit SynonymArg(SynonymName syn_name)
      : Argument(),
        syn_name_(syn_name),
        entity_type_(EntityType::kUndetermined) {}

  explicit SynonymArg(SynonymName syn_name, EntityType entity_type)
      : Argument(), syn_name_(syn_name), entity_type_(entity_type) {}

  inline static Elem get_full_name(ArgumentPtr &arg) {
    auto syn_arg = dynamic_cast<SynonymArg *>(arg.get());
    return syn_arg->get_full_name();
  }

  // Weaker equal that returns true if both arguments
  // are synonyms (incl AttrRefArg that inherits from SynonymArg)
  // and have the same synonym name
  inline static bool CompareSynonym(
      ArgumentPtr &LHS, ArgumentPtr &RHS) {
    auto lhs_syn = dynamic_cast<SynonymArg *>(LHS.get());
    auto rhs_syn = dynamic_cast<SynonymArg *>(RHS.get());
    if (lhs_syn == nullptr || rhs_syn == nullptr) {
      return false;
    }

    return lhs_syn->get_syn_name() == rhs_syn->get_syn_name();
  }

  inline bool IsSynonym() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline bool IsIdentType() override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    return master_entity_factory_.is_ident(entity_type_);
  }

  inline bool IsIntegerType() override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    return master_entity_factory_.is_integer(entity_type_);
  }

  inline SynonymName get_syn_name() { return syn_name_; }
  inline EntityType get_entity_type() { return entity_type_; }

  inline virtual Elem get_full_name() {
    return syn_name_;
  }

  inline virtual void set_entity_type(EntityType entity_type) {
    entity_type_ = entity_type;
  }

  inline bool Validate(
      std::unordered_set<EntityType> &valid_entity_types) override {
    if (entity_type_ == EntityType::kUndetermined) return false;

    // Verify that the synonym type matches the
    // context of the clause, e.g Modifies(stmt, var)
    return valid_entity_types.count(entity_type_);
  }

  void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override;

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Synonym: " << syn_name_;
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
        && entity_type_ == arg->entity_type_;
  }

 protected:
  SynonymName syn_name_;
  EntityType entity_type_;
};
}  // namespace qps
