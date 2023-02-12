#pragma once

#include "IntEntity.h"

namespace models {

class Stmt : public IntEntity {
 public:
  explicit Stmt(int number) : IntEntity(number) {}
};

class ReadStmt : public Stmt {
 public:
  explicit ReadStmt(int number) : Stmt(number) {}
};

class PrintStmt : public Stmt {
 public:
  explicit PrintStmt(int number) : Stmt(number) {}
};

class AssignStmt : public Stmt {
 public:
  explicit AssignStmt(int number) : Stmt(number) {}
};

class CallStmt : public Stmt {
 public:
  explicit CallStmt(int number) : Stmt(number) {}
};

class ContainerStmt : public Stmt {
 public:
  explicit ContainerStmt(int number) : Stmt(number) {}
};

class WhileStmt : public ContainerStmt {
 public:
  explicit WhileStmt(int number) : ContainerStmt(number) {}
};

class IfStmt : public ContainerStmt {
 public:
  explicit IfStmt(int number) : ContainerStmt(number) {}
};
}  // namespace models
