#pragma once

#include <unordered_set>
#include <memory>

#include "Argument.h"

namespace qps {
class IntegerArg : public Argument {
 public:
  explicit IntegerArg(int number) : Argument(), number_(number) {}

  inline bool IsStmtRef() override { return true; }
  inline bool IsIntegerType() override { return true; }

  inline int get_number() { return number_; }

  inline bool Validate(
      std::unordered_set<EntityType> &valid_entity_types) override {
    for (auto &entity_type : valid_entity_types) {
      if (master_entity_factory_.is_integer(entity_type)) {
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

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Int Arg: " << number_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<IntegerArg>(*this);
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
}  // namespace qps
