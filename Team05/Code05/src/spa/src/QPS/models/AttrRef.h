#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>

#include "QPS/models/AttrType.h"
#include "QPS/models/EntityType.h"
#include "QPS/models/Entity.h"
#include "PQL.h"

namespace qps {
class AttrRef {
 public:
  inline static std::string kAttrRefDelimiter = PQL::kPeriodToken;

  inline static AttrType get_attr_type(AttrName attr_name) {
    return kAttrNameToTypeMap.at(attr_name);
  }

  inline static bool is_attr_name(AttrName attr_name) {
    return kAttrNameToTypeMap.count(attr_name);
  }

  inline static bool is_attr_ref(std::string str) {
    auto index = str.find(PQL::kAttrRefDelimiter);
    // "." doesn't exist
    if (index == std::string::npos) return false;
    auto [syn, attr_name] = split_attr_ref(str);
    return PQL::is_synonym(syn)
        && is_attr_name(attr_name);
  }

  inline static bool ValidateAttrRef(
      AttrType attr_type, EntityType entity_type) {
    auto &attr_name_types = kAttrTypeToEntitiesMap.at(attr_type);
    return attr_name_types.count(entity_type);
  }

  // Splits an attrRef (e.g s.stmt#) by the '.' delimiter
  // Returns a pair of strings [ syn_name, attr_name ]
  // that is before and after the delimiter respectively.
  inline static std::pair<std::string, std::string> split_attr_ref(
      std::string str) {
    auto index = str.find(kAttrRefDelimiter);
    std::string syn_name = str.substr(0, index);
    std::string attr_name = str.substr(index + 1);
    return {syn_name, attr_name};
  }

  // Given a syn_name and attr_name, joins attrRef back together
  inline static std::string join_attr_ref(
      SynonymName syn_name, AttrType attr_type
  ) {
    return syn_name
        + kAttrRefDelimiter
        + kAttrTypeToNameMap.at(attr_type);
  }

  // Give an AttrType, return true if its type is IDENT.
  // Note that this does not have to correspond to the type of
  // the synonym.
  // E.g read.varName is IDENT even though read is a stmt
  // and stmt is an INTEGER type.
  inline static bool is_attr_type_ident(AttrType attr_type) {
    return attr_type == AttrType::kProcName
        || attr_type == AttrType::kVarName;
  }

  // Give an AttrName, return true if its type is INTEGER.
  inline static bool is_attr_type_integer(AttrType attr_type) {
    return attr_type == AttrType::kValue
        || attr_type == AttrType::kStmtNum;
  }

  // A secondary attr_ref is defined as an attr_ref that is
  // not the same as its index.
  // E.g stmt.stmt# is the same as its index, but
  // call.procName is not the same.
  // In ADVANCED SPA requirements, only
  // call, print, and read can have secondary attr_refs.
  inline static bool is_attr_ref_secondary(
      EntityType entity_type, AttrType attr_type) {
    switch (entity_type) {
      case EntityType::kRead:
      case EntityType::kPrint: {
        return attr_type == AttrType::kVarName;
      }
      case EntityType::kCall: {
        return attr_type == AttrType::kProcName;
      }
      default: {
        return false;
      }
    }
  }

 private:
  // Maps an AttrName (e.g stmt#) to a hashset of all
  // entities that can be paired with that AttrName.
  // e.g. varName is mapped to { variable, read, print }
  inline static std::unordered_map<AttrType, std::unordered_set<EntityType>>
      kAttrTypeToEntitiesMap{
      {AttrType::kProcName, {EntityType::kProcedure, EntityType::kCall}},
      {AttrType::kVarName,
       {EntityType::kVariable, EntityType::kRead, EntityType::kPrint}},
      {AttrType::kValue, {EntityType::kConstant}},
      {AttrType::kStmtNum, Entity::get_all_stmt_entities()}
  };

  inline static std::unordered_map<AttrName, AttrType> kAttrNameToTypeMap{
      {PQL::kProcedureAttrName, AttrType::kProcName},
      {PQL::kVariableAttrName, AttrType::kVarName},
      {PQL::kValueAttrName, AttrType::kValue},
      {PQL::kStmtAttrName, AttrType::kStmtNum}
  };

  inline static std::unordered_map<AttrType, AttrName> kAttrTypeToNameMap{
      {AttrType::kProcName, PQL::kProcedureAttrName},
      {AttrType::kVarName, PQL::kVariableAttrName},
      {AttrType::kValue, PQL::kValueAttrName},
      {AttrType::kStmtNum, PQL::kStmtAttrName}
  };
};
}  // namespace qps
