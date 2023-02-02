#pragma once

#include <exception>

class InvalidPqlException : public std::exception {
 public:
  InvalidPqlException(char *msg) : message(msg) {};
  char *what() { return message; }
 private:
  char *message;
};

class PqlSyntaxErrorException : public InvalidPqlException { ;
 public:
  PqlSyntaxErrorException(char *msg) : InvalidPqlException(msg) {}
};

class PqlSemanticErrorException : public InvalidPqlException {
 public:
  PqlSemanticErrorException(char *msg) : InvalidPqlException(msg) {};
};