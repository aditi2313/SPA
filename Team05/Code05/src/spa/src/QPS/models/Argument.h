#pragma once
#include <sstream>
#include <string>
#include "models/types.h"

using models::Synonym;

namespace qps {

enum ArgumentType {
  kInteger,
  kIdent,
  kSynonym,
  kWildcard,
  kExpression
};

// An argument for a clause.
// e.g. Clause(Argument, Argument)
// It can be a synonym for statement, procedure, variable,
// character strings, wildcard, or expressions for exact/partial matches
// TODO(JL): replace string with OOP and include wildcards etc.
class Argument {
 public:
  Argument(ArgumentType arg_type) : arg_type_(arg_type) {}
  const ArgumentType arg_type_;

  // synonym | _ | INTEGER
  bool inline IsStmtRef() {
    return (
        arg_type_ == ArgumentType::kInteger
            || arg_type_ == ArgumentType::kWildcard
            || arg_type_ == ArgumentType::kSynonym
    );
  }

  // synonym | _ | "ident"
  bool inline IsEntRef() {
    return (
        arg_type_ == ArgumentType::kIdent
            || arg_type_ == ArgumentType::kWildcard
            || arg_type_ == ArgumentType::kSynonym
    );
  }

  bool inline IsExact() {
    return (arg_type_ == ArgumentType::kInteger ||
        arg_type_ == ArgumentType::kIdent);
  }

  bool inline IsWildcard() {
    return arg_type_ == ArgumentType::kWildcard;
  }

  bool operator==(Argument const &other) const {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);

    if (ti1 != ti2) return false;

    // TODO(JL): continue comparing member variables
    // for different type
    return true;
  }
};

class Wildcard : public Argument {
 public:
  Wildcard() : Argument(ArgumentType::kWildcard) {}
};

class SynonymArg : public Argument {
 public:
  SynonymArg(Synonym syn, models::EntityId entity_id)
      : Argument(ArgumentType::kSynonym), syn_(syn), entity_id_(entity_id) {}

  inline Synonym get_syn() { return syn_; }
  models::EntityId get_entity_id() { return entity_id_; }

 private:
  Synonym syn_;
  models::EntityId entity_id_;
};

class IdentArg : public Argument {
 public:
  IdentArg(std::string ident) :
      Argument(ArgumentType::kIdent), ident_(ident) {}
 private:
  std::string ident_;
};

class IntegerArg : public Argument {
 public :
  IntegerArg(int number) :
      Argument(ArgumentType::kInteger), number_(number) {}
 private:
  int number_;
};

class ExpressionArg : public Argument {
 public:
  ExpressionArg(std::string expr) :
      Argument(ArgumentType::kExpression), expr_(expr) {}
 private:
  std::string expr_;  // Expression
};

using ArgumentPtr = std::unique_ptr<Argument>;
}  // namespace qps

