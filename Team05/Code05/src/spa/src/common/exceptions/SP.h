#pragma once
#include <exception>
#include <string>
// exception file for SP
namespace sp {
class ParseException : public std::exception {
 public:
  explicit ParseException(const std::string msg) : message(msg) {}
  const char* what() const throw() override { return message.c_str(); }

 private:
  const std::string message;
};

class ParseRelationSyntaxException : public ParseException {
 public:
  explicit ParseRelationSyntaxException(std::string additional)
      : ParseException(kParseRelationSyntaxMessage + additional) {}
  ParseRelationSyntaxException()
      : ParseException(kParseRelationSyntaxMessage) {}

 private:
  static const char kParseRelationSyntaxMessage[];
};
}  // namespace sp
