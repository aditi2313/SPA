#include "SP.h"

namespace sp {

void AssertExpectedToken(Token to_test, Token expected, std::string token) {
  if (to_test != expected) {
    throw ParseException("Wrong token received: " + token);
  }
}

void AssertExpectedToken(std::string prefix, Token to_test, Token expected) {
  if (to_test != expected) {
    throw ParseException(prefix
                         + "Wrong token received: " + TokenToString(to_test)
                         + ", expected: " + TokenToString(expected));
  }
}

void AssertExpectedToken(Token to_test, Token expected) {
  return AssertExpectedToken("", to_test, expected);
}

const char LexerException::kLexerExceptionMessage[] =
    "Exception occurred at Lexer: ";

const char ParseProcedureSyntaxException::kParseProcedureSyntaxMessage[] =
    "Invalid syntax at parsing of procedure: ";

const char ParseStmtLstSyntaxException::kParseStmtLstSyntaxMessage[] =
    "Invalid syntax at parsing of statement list: ";

const char ParseAssignSyntaxException::kParseAssignSyntaxMessage[] =
    "Invalid syntax at parsing of assignment: ";

const char ParseRelationSyntaxException::kParseRelationSyntaxMessage[] =
    "Invalid syntax at parsing of relation: ";

const char ParseFactorSyntaxException::kParseFactorSyntaxMessage[] =
    "Invalid syntax at parsing of factor: ";
}  // namespace sp
