#pragma once

#include <unordered_set>
#include <memory>

#include "Argument.h"

namespace qps {
class Wildcard : public Argument {
 public:
  Wildcard()
      : Argument(), entity_type_(EntityType::kUndetermined) {}

  inline bool IsWildcard() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline void set_entity_type(EntityType entity_type) {
    entity_type_ = entity_type;
  }

  inline bool Validate(
      std::unordered_set<EntityType> &valid_entity_types) override {
    return true;
  }

  inline void InitializeEntities(
      Table &table,
      pkb::PKBReadPtr &pkb,
      EntitySet &results) override {
    if (entity_type_ == EntityType::kUndetermined) return;

    results = master_entity_factory_.GetAllFromPKB(
        entity_type_, pkb);
  }

  inline std::ostream &dump(std::ostream &str) const override {
    return str << "Wildcard";
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<Wildcard>(*this);
  }

  inline bool operator==(Argument &other) override {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);
    return ti1 == ti2;
  }

 private:
  EntityType entity_type_;
};
}  // namespace qps
