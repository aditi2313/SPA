#pragma once
#include <sstream>
#include <string>
#include <memory>

#include "models/types.h"
#include "QPS/models/Synonym.h"

using models::SynonymName;

namespace qps {
// An argument for a clause.
// e.g. Clause(Argument, Argument)
// It can be a synonym for statement, procedure, variable,
// character strings, wildcard, or expressions for exact/partial matches
// TODO(JL): replace string with OOP and include wildcards etc.
class Argument {
 public:
  // synonym | _ | INTEGER
  virtual bool IsStmtRef() { return false; }
  // synonym | _ | "ident"
  virtual bool IsEntRef() { return false; }
  virtual bool IsWildcard() { return false; }
  virtual bool IsSynonym() { return false; }
  virtual bool IsExpression() { return false; }

  bool operator==(Argument const &other) const {
    const std::type_info &ti1 = typeid(*this);
    const std::type_info &ti2 = typeid(other);

    if (ti1 != ti2) return false;

    // TODO(JL): continue comparing member variables
    // for different type
    return true;
  }

  virtual std::unique_ptr<Argument> Copy() = 0;

  virtual ~Argument() = 0;
  inline virtual std::ostream &dump(std::ostream &str) const {
    return str << "Argument";
  }
  friend inline std::ostream &operator<<(std::ostream &o, Argument &base) {
    return base.dump(o);
  }
};

class Wildcard : public Argument {
 public:
  Wildcard() : Argument() {}

  inline bool IsWildcard() override { return true; }
  inline bool IsEntRef() override { return true; }
  inline bool IsStmtRef() override { return true; }

  inline std::ostream &dump(std::ostream &str) const override {
    return str << "Wildcard";
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<Wildcard>(*this);
  }
};

class SynonymArg : public Argument {
 public:
  explicit SynonymArg(SynonymName syn_name)
      : Argument(), syn_name_(syn_name) {}

  inline bool IsSynonym() override { return true; }

  inline SynonymName get_syn_name() { return syn_name_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Synonym: " << syn_name_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<SynonymArg>(*this);
  }

 private:
  SynonymName syn_name_;
};

class IdentArg : public Argument {
 public:
  explicit IdentArg(std::string ident) :
      Argument(), ident_(ident) {}

  inline bool IsEntRef() override { return true; }

  inline std::string get_ident() { return ident_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Ident Arg: " << ident_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<IdentArg>(*this);
  }

 private:
  std::string ident_;
};

class IntegerArg : public Argument {
 public :
  explicit IntegerArg(int number) :
      Argument(), number_(number) {}

  inline bool IsStmtRef() override { return true; }

  inline int get_number() { return number_; }

  inline std::ostream &dump(std::ostream &str) const override {
    str << "Int Arg: " << number_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<IntegerArg>(*this);
  }

 private:
  int number_;
};

class ExpressionArg : public Argument {
 public:
  explicit ExpressionArg(std::string expr, bool is_exact) :
      Argument(), expr_(expr), is_exact_(is_exact) {}

  inline bool IsExpression() override { return true; }
  inline std::string get_expression() { return expr_; }
  inline bool is_exact() { return is_exact_; }
  inline std::ostream &dump(std::ostream &str) const override {
    str << "Expr Arg: " << expr_;
    return str;
  }
  inline std::unique_ptr<Argument> Copy() override {
    return std::make_unique<ExpressionArg>(*this);
  }
  
 private:
  std::string expr_;  // Expression
  bool is_exact_;
};

using ArgumentPtr = std::unique_ptr<Argument>;
}  // namespace qps
