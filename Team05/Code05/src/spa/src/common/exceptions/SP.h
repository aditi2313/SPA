#pragma once

#include <exception>
// exception file for SP
namespace sp {
class ParseException : public std::exception {
 public:
  explicit ParseException(const char *msg) : message(msg) {}
  const char *what() { return message; }

 private:
  const char *message;
};

class ParseRelationSyntaxException : public ParseException {
 public:
  explicit ParseRelationSyntaxException()
      : ParseException("Invalid synatx at parsing of relation") {}
};
}  // namespace sp
