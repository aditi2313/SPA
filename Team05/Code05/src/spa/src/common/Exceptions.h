#pragma once

#include <exception>

class InvalidPqlException : public std::exception {
 public:
  InvalidPqlException(const char *msg) : message(msg) {};
  const char *what() { return message; }
 private:
  const char *message;
};

class PqlSyntaxErrorException : public InvalidPqlException { ;
 public:
  PqlSyntaxErrorException(const char *msg) : InvalidPqlException(msg) {}
};

class PqlSemanticErrorException : public InvalidPqlException {
 public:
  PqlSemanticErrorException(const char *msg) : InvalidPqlException(msg) {};
};