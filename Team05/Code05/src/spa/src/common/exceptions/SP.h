#pragma once
#include <exception>
#include <string>

#include "models/AST/Token.h"

// exception file for SP
namespace sp {

// TODO(Gab): Apply this function to the rest of the parser
void AssertExpectedToken(Token to_test, Token expected, std::string token);
void AssertExpectedToken(std::string prefix, Token to_test, Token expected);
void AssertExpectedToken(Token to_test, Token expected);

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

class ParseProcedureSyntaxException : public ParseException {
 public:
  explicit ParseProcedureSyntaxException(std::string additional)
      : ParseException(kParseProcedureSyntaxMessage + additional) {}
  ParseProcedureSyntaxException()
      : ParseException(kParseProcedureSyntaxMessage) {}

  static const char kParseProcedureSyntaxMessage[];
};

class ParseStmtLstSyntaxException : public ParseException {
 public:
  explicit ParseStmtLstSyntaxException(std::string additional)
      : ParseException(kParseStmtLstSyntaxMessage + additional) {}
  ParseStmtLstSyntaxException()
      : ParseException(kParseStmtLstSyntaxMessage) {}

  static const char kParseStmtLstSyntaxMessage[];
};

class ParseStmtSyntaxException : public ParseException {
 public:
  explicit ParseStmtSyntaxException(std::string additional)
      : ParseException(kParseStmtSyntaxMessage + additional) {}
  ParseStmtSyntaxException()
      : ParseException(kParseStmtSyntaxMessage) {}

  static const char kParseStmtSyntaxMessage[];
};

class ParseAssignSyntaxException : public ParseException {
public:
  explicit ParseAssignSyntaxException(std::string additional)
      : ParseException(kParseAssignSyntaxMessage + additional) {}
  ParseAssignSyntaxException() : ParseException(kParseAssignSyntaxMessage) {}

  static const char kParseAssignSyntaxMessage[];
};

class ParseCallSyntaxException : public ParseException {
public:
  explicit ParseCallSyntaxException(std::string additional)
      : ParseException(kParseCallSyntaxMessage + additional) {}
  ParseCallSyntaxException() : ParseException(kParseCallSyntaxMessage) {}

  static const char kParseCallSyntaxMessage[];
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

}  // namespace sp
