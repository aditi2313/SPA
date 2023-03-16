#pragma once

#include <exception>

class InvalidPqlException : public std::exception {
 public:
  explicit InvalidPqlException(const char *msg) : message(msg) {}
  const char *what() const throw() override { return message; }

 private:
  const char *message;
};

class PqlSyntaxErrorException : public InvalidPqlException {
 public:
  explicit PqlSyntaxErrorException(const char *msg)
      : InvalidPqlException(msg) {}
};

class PqlSemanticErrorException : public InvalidPqlException {
 public:
  explicit PqlSemanticErrorException(const char *msg)
      : InvalidPqlException(msg) {}
};

class QpsEvaluatorException : public std::exception {
 public:
  explicit QpsEvaluatorException(const char *msg) : message(msg) {}
  const char *what() const throw() override { return message; }

 private:
  const char *message;
};

class NotImplementedException : public std::exception {
 public:
  char *what() { return const_cast<char *>("Not Implemented"); }
};
