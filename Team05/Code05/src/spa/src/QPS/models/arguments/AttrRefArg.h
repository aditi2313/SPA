#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

#include "Argument.h"
#include "SynonymArg.h"

namespace qps {

class AttrRefArg : public SynonymArg {
 public:
  explicit AttrRefArg(SynonymName syn_name, AttrName attr_name)
      : SynonymArg(syn_name),
        attr_name_(attr_name),
        entity_type_(EntityType::kUndetermined) {}

  inline bool IsIdentType() override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    return PQL::is_attr_name_ident(attr_name_);
  }

  inline bool IsIntegerType() override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    return PQL::is_attr_name_integer(attr_name_);
  }

  inline Elem get_full_name() override {
    return PQL::join_attr_ref(syn_name_, attr_name_);
  }

  inline void set_entity_type(EntityType entity_type) override {
    entity_type_ = entity_type;
    is_secondary_attr_value_ = PQL::is_attr_ref_secondary(
        entity_type, attr_name_);
  }

  inline Entity get_attr_value(
      const pkb::PKBReadPtr &pkb, const Entity &index) {
    if (!is_secondary_attr_value_) return index;
    return master_entity_factory_.GetAttrValue(entity_type_, index, pkb);
  }

  inline bool Validate(
      std::unordered_set<EntityType> &valid_entity_types) override {
    if (entity_type_ == EntityType::kUndetermined) return false;
    return PQL::ValidateAttrRef(attr_name_, entity_type_);
  }

  void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override;

  void UpdateTableWithAttrValue(
      pkb::PKBReadPtr &pkb,
      Table &query_table,
      bool &is_table_initialized);

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Synonym: " << syn_name_ << " with: " << attr_name_;
    return str;
  }

  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<SynonymArg>(*this);
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    if (ti1 != ti2) return false;

    auto arg = dynamic_cast<AttrRefArg *>(&other);
    return syn_name_ == arg->syn_name_
        && entity_type_ == arg->entity_type_
        && attr_name_ == arg->attr_name_;
  }

 private:
  SynonymName syn_name_;
  EntityType entity_type_;
  AttrName attr_name_;
  bool is_secondary_attr_value_ = false;
};
}  // namespace qps
