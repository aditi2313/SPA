#pragma once

#include "IntEntity.h"

namespace models {

class Stmt : public IntEntity {
 public:
  Stmt(int number) : IntEntity(number) {}
};

class ReadStmt : public Stmt {
 public:
  ReadStmt(int number) : Stmt(number) {}
};

class PrintStmt : public Stmt {
 public:
  PrintStmt(int number) : Stmt(number) {}
};

class AssignStmt : public Stmt {
 public:
  AssignStmt(int number) : Stmt(number) {}
};

class CallStmt : public Stmt {
 public:
  CallStmt(int number) : Stmt(number) {}
};

class ContainerStmt : public Stmt {
 public:
  ContainerStmt(int number) : Stmt(number) {}
};

class WhileStmt : public ContainerStmt {
 public:
  WhileStmt(int number) : ContainerStmt(number) {}
};

class IfStmt : public ContainerStmt {
 public:
  IfStmt(int number) : ContainerStmt(number) {}

};
}  // namespace models