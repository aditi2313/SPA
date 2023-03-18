#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

#include "Argument.h"

namespace qps {

class SynonymArg : public Argument {
 public:
  explicit SynonymArg(SynonymName syn_name)
      : Argument(), syn_name_(syn_name) {}

  explicit SynonymArg(SynonymName syn_name, EntityName entity_name)
      : Argument(), syn_name_(syn_name), entity_name_(entity_name) {}

  static inline SynonymName get_full_name(ArgumentPtr &arg) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
    return syn_arg->get_full_name();
  }

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
  inline EntityName get_entity_name() { return entity_name_; }

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

  inline bool is_secondary_attr_ref() {
    return !attr_name_.empty()
        && PQL::is_attr_ref_secondary(entity_name_, attr_name_);
  }

  inline Entity get_secondary_attr_value(
      const pkb::PKBReadPtr &pkb, const Entity &index
  ) {
    return master_entity_factory_.GetAttrValue(entity_name_, index, pkb);
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

  static inline SynonymName get_syn_name(ArgumentPtr &arg) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
    return syn_arg->get_syn_name();
  }

  static inline SynonymName get_entity_name(ArgumentPtr &arg) {
    SynonymArg *syn_arg = dynamic_cast<SynonymArg *>(arg.get());
    return syn_arg->get_entity_name();
  }

 private:
  SynonymName syn_name_;
  EntityName entity_name_;
  AttrName attr_name_;
};
}  // namespace qps
