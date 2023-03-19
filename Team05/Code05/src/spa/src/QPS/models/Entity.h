#pragma once

#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

#include "models/types.h"
#include "PQL.h"
#include "EntityType.h"

namespace qps {

// Represents a:
// Procedure | Stmt (Read | Print | Assign | Call | While | If)
// Variable | Constant
class Entity {
 public:
  using Value = std::variant<int, std::string>;

  Entity() {}
  explicit Entity(int int_value) : value_(int_value) {}
  explicit Entity(std::string str) : value_(str) {}

  inline static bool const is_entity_name(EntityName const entity_name) {
    return kEntityNameToEntityTypeMap.count(entity_name);
  }

  inline static EntityType get_entity_type(EntityName const entity_name) {
    return kEntityNameToEntityTypeMap.at(entity_name);
  }

  inline static std::unordered_set<EntityType> get_all_entities() {
    std::unordered_set<EntityType> entities;
    for (auto &[name, type] : kEntityNameToEntityTypeMap) {
      entities.insert(type);
    }
    return entities;
  }

  inline static std::unordered_set<EntityType> get_all_stmt_entities() {
    return kAllStmtEntityTypes;
  }

  inline Value get_value() const {
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
    return value_ == other.value_;
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
    return value_ == other.value_;
  }

  inline std::size_t hash() const {
    return std::hash<decltype(value_)>{}(value_);
  }

  friend inline std::ostream &operator<<(
      std::ostream &o, const Entity &entity) {
    return o << "Entity: " <<
             (entity.is_str()
              ? entity.get_str()
              : std::to_string(entity.get_int()));
  }

  ~Entity() = default;

  friend std::hash<Entity>;

 private:
  Value value_;
  inline static std::unordered_set<EntityType> kAllStmtEntityTypes{
      EntityType::kStmt, EntityType::kRead,
      EntityType::kPrint, EntityType::kCall,
      EntityType::kWhile, EntityType::kIf, EntityType::kAssign
  };

  inline static std::unordered_map<EntityName, EntityType>
      kEntityNameToEntityTypeMap{
      {PQL::kStmtEntityName, EntityType::kStmt},
      {PQL::kReadEntityName, EntityType::kRead},
      {PQL::kPrintEntityName, EntityType::kPrint},
      {PQL::kCallEntityName, EntityType::kCall},
      {PQL::kWhileEntityName, EntityType::kWhile},
      {PQL::kIfEntityName, EntityType::kIf},
      {PQL::kAssignEntityName, EntityType::kAssign},
      {PQL::kVariableEntityName, EntityType::kVariable},
      {PQL::kConstantEntityName, EntityType::kConstant},
      {PQL::kProcedureEntityName, EntityType::kProcedure}
  };
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
