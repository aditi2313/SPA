#pragma once

#include <unordered_set>
#include <memory>

#include "Argument.h"

namespace qps {
class Wildcard : public Argument {
 public:
  Wildcard() : Argument() {}

  inline bool IsWildcard() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline void set_entity_name(EntityName entity_name) {
    entity_name_ = entity_name;
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
  EntityName entity_name_;
};
}  // namespace qps
