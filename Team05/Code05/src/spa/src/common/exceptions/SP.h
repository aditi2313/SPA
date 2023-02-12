#pragma once
#include <exception>
#include <string>
// exception file for SP
namespace sp {
class ParseException : public std::exception {
 public:
  explicit ParseException(const std::string msg) : message(msg) {}
  const std::string what() { return message; }

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
  static const std::string kParseRelationSyntaxMessage;
};
}  // namespace sp
