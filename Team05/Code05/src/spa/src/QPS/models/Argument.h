#pragma once
#include <sstream>
#include <string>
#include <memory>

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
  explicit Argument(ArgumentType arg_type) : arg_type_(arg_type) {}

  // synonym | _ | INTEGER
  bool inline IsStmtRef() {
    return (
        arg_type_ == ArgumentType::kInteger
            || arg_type_ == ArgumentType::kWildcard
            || arg_type_ == ArgumentType::kSynonym);
  }

  // synonym | _ | "ident"
  bool inline IsEntRef() {
    return (
        arg_type_ == ArgumentType::kIdent
            || arg_type_ == ArgumentType::kWildcard
            || arg_type_ == ArgumentType::kSynonym);
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

  virtual ~Argument() = 0;
  inline virtual std::ostream &dump(std::ostream &str) const {
    return str << "Argument";
  }
  friend inline std::ostream &operator<<(std::ostream &o, Argument &base) {
    return base.dump(o);
  }

 protected:
  const ArgumentType arg_type_;
};

class Wildcard : public Argument {
 public:
  Wildcard() : Argument(ArgumentType::kWildcard) {}

  inline std::ostream &dump(std::ostream &str) const override {
    return str << "Wildcard";
  }
};

class SynonymArg : public Argument {
 public:
  SynonymArg(Synonym syn, models::EntityId entity_id)
      : Argument(ArgumentType::kSynonym), syn_(syn), entity_id_(entity_id) {}

  inline Synonym get_syn() { return syn_; }
  models::EntityId get_entity_id() { return entity_id_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Synonym: " << syn_ << "->" << entity_id_;
    return str;
  }

 private:
  Synonym syn_;
  models::EntityId entity_id_;
};

class IdentArg : public Argument {
 public:
  explicit IdentArg(std::string ident) :
      Argument(ArgumentType::kIdent), ident_(ident) {}

  inline std::string get_ident() { return ident_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Ident Arg: " << ident_;
    return str;
  }
 private:
  std::string ident_;
};

class IntegerArg : public Argument {
 public :
  explicit IntegerArg(int number) :
      Argument(ArgumentType::kInteger), number_(number) {}

  inline int get_number() { return number_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Int Arg: " << number_;
    return str;
  }
 private:
  int number_;
};

class ExpressionArg : public Argument {
 public:
  explicit ExpressionArg(std::string expr) :
      Argument(ArgumentType::kExpression), expr_(expr) {}

  inline std::string get_expression() { return expr_; }
  inline std::ostream &dump(std::ostream &str) const override {
    str << "Expr Arg: " << expr_;
    return str;
  }
 private:
  std::string expr_;  // Expression
};

using ArgumentPtr = std::unique_ptr<Argument>;
}  // namespace qps

