#pragma once

#include <unordered_set>
#include <memory>
#include <string>

#include "Argument.h"

namespace qps {
class IdentArg : public Argument {
 public:
  explicit IdentArg(std::string ident) : Argument(), ident_(ident) {}

  inline bool IsEntRef() override { return true; }
  inline bool IsIdentType() override { return true; }

  inline std::string get_ident() { return ident_; }

  inline bool Validate(
      std::unordered_set<EntityType> &valid_entity_types) override {
    for (auto &entity_type : valid_entity_types) {
      if (master_entity_factory_.is_ident(entity_type)) {
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

 private:
  std::string ident_;
};
}  // namespace qps
