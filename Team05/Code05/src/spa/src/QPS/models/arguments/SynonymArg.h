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

  inline bool IsSynonym() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline bool IsIdentType() override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    if (!attr_name_.empty())
      return PQL::is_attr_name_ident(attr_name_);
    return master_entity_factory_.is_ident(entity_type_);
  }

  inline bool IsIntegerType() override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    if (!attr_name_.empty())
      return PQL::is_attr_name_integer(attr_name_);
    return master_entity_factory_.is_integer(entity_type_);
  }

  inline SynonymName get_syn_name() { return syn_name_; }
  inline EntityType get_entity_type() { return entity_type_; }

  inline virtual Elem get_full_name() {
    return syn_name_;
  }

  inline void set_entity_type(EntityType entity_type) {
    entity_type_ = entity_type;
  }

  inline bool Validate(
      std::unordered_set<EntityType> &valid_entity_types) override {
    // Synonym has not been declared
    if (entity_type_ == EntityType::kUndetermined) return false;

    // Verify that the synonym type matches the
    // context of the clause, e.g Modifies(stmt, var)
    return valid_entity_types.count(entity_type_);
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
          entity_type_, pkb);
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
      Table &query_table,
      bool &is_table_initialized);

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

 private:
  SynonymName syn_name_;
  EntityType entity_type_;
};
}  // namespace qps
