#pragma once

#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <unordered_set>

#include "models/types.h"
#include "PQL.h"
#include <cassert>

using models::EntityName;

namespace qps {
// Represents a:
// Procedure | Stmt (Read | Print | Assign | Call | While | If)
// Variable | Constant
class Entity {
 public:
  using EntityValue = std::variant<int, std::string>;

  Entity() {}
  explicit Entity(int int_value) : value_(int_value) {}
  explicit Entity(std::string str) : value_(str) {}

  inline EntityValue get_value() const {
    return value_;
  }

  inline int get_int() const {
    return std::get<int>(value_);
  }

  inline std::string get_str() const {
    return std::get<std::string>(value_);
  }

  inline bool is_int() const {
    return std::holds_alternative<int>(value_);
  }

  inline bool is_str() const {
    return std::holds_alternative<std::string>(value_);
  }

  inline std::string to_str() const {
    return is_int() ? std::to_string(get_int())
                    : get_str();
  }

  inline bool operator==(const Entity &other) const {
    return value_ == other.value_
        && entity_name_ == other.entity_name_;
  }

  inline bool operator!=(const Entity &other) const {
    return !(*this == other);
  }

  inline bool operator<(const Entity &other) const {
    assert((is_int() && other.is_int())
               || (is_str() && other.is_str()));

    return is_int() ? get_int() < other.get_int()
                    : get_str() < other.get_str();
  }

  inline bool WeakEqual(const Entity &other) const {
    return value_ == other.value_
        && PQL::get_base_entity_name(entity_name_)
            == PQL::get_base_entity_name(other.entity_name_);
  }

  inline std::size_t hash() const {
    return std::hash<decltype(value_)>{}(value_);
  }

  ~Entity() = default;

  friend std::hash<Entity>;

 private:
  EntityName entity_name_;
  EntityValue value_;
};

using EntitySet = std::unordered_set<Entity>;
}  // namespace qps

template<>
class std::hash<qps::Entity> {
 public:
  std::size_t operator()(const qps::Entity &entity) const {
    return std::hash<decltype(entity.value_)>{}(entity.value_);
  }
};
