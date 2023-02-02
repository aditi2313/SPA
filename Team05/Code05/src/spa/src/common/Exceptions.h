#pragma once
#include <exception>

class Exceptions {};

class NotImplementedException : public std::exception {
 public:
  char* what() { return "Not Implemented"; }
};
