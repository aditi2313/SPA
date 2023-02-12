#pragma once

#include "IntEntity.h"

namespace models {

class Stmt : public IntEntity {
 public:
  explicit Stmt(int number) : IntEntity(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<Stmt>(*this);
  }
};

class ReadStmt : public Stmt {
 public:
  explicit ReadStmt(int number) : Stmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<ReadStmt>(*this);
  }
};

class PrintStmt : public Stmt {
 public:
  explicit PrintStmt(int number) : Stmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<PrintStmt>(*this);
  }
};

class AssignStmt : public Stmt {
 public:
  explicit AssignStmt(int number) : Stmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<AssignStmt>(*this);
  }
};

class CallStmt : public Stmt {
 public:
  explicit CallStmt(int number) : Stmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<CallStmt>(*this);
  }
};

class ContainerStmt : public Stmt {
 public:
  explicit ContainerStmt(int number) : Stmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<ContainerStmt>(*this);
  }
};

class WhileStmt : public ContainerStmt {
 public:
  explicit WhileStmt(int number) : ContainerStmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<WhileStmt>(*this);
  }
};

class IfStmt : public ContainerStmt {
 public:
  explicit IfStmt(int number) : ContainerStmt(number) {}

  inline EntityPtr Copy() override {
    return std::make_unique<ContainerStmt>(*this);
  }
};
}  // namespace models
