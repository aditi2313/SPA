#pragma once
#include <exception>
#include <string>

#include "models/AST/Token.h"
// exception file for SP
namespace sp {

// TODO(Gab): Apply this function to the rest of the parser
void AssertExpectedToken(Token to_test, Token expected, std::string token);

class LexerException : public std::exception {
 public:
  explicit LexerException(const std::string msg)
      : message(kLexerExceptionMessage + msg) {}
  const char* what() const throw() override { return message.c_str(); }

 private:
  const std::string message;
  static const char kLexerExceptionMessage[];
};

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

class ParseFactorSyntaxException : public ParseException {
 public:
  explicit ParseFactorSyntaxException(std::string additional)
      : ParseException(kParseFactorSyntaxMessage + additional) {}
  ParseFactorSyntaxException() : ParseException(kParseFactorSyntaxMessage) {}

 private:
  static const char kParseFactorSyntaxMessage[];
};

class ParseAssignSyntaxException : public ParseException {
 public:
  explicit ParseAssignSyntaxException(std::string additional)
      : ParseException(kParseAssignSyntaxMessage + additional) {}
  ParseAssignSyntaxException() : ParseException(kParseAssignSyntaxMessage) {}

 private:
  static const char kParseAssignSyntaxMessage[];
};

}  // namespace sp
