#include "SP.h"

namespace sp {

void AssertExpectedToken(std::string prefix, Token to_test, Token expected) {
  if (to_test != expected) {
    throw ParseException(prefix
                         + "Wrong token received: " + TokenToString(to_test)
                         + ", expected: " + TokenToString(expected));
  }
}

const char LexerException::kLexerExceptionMessage[] =
    "Exception occurred at Lexer: ";

const char ParseProcedureSyntaxException::kParseProcedureSyntaxMessage[] =
    "Invalid syntax at parsing of procedure: ";

const char ParseStmtLstSyntaxException::kParseStmtLstSyntaxMessage[] =
    "Invalid syntax at parsing of statement list: ";

const char ParseStmtSyntaxException::kParseStmtSyntaxMessage[] =
    "Invalid syntax at parsing of statement: ";

const char ParseAssignSyntaxException::kParseAssignSyntaxMessage[] =
    "Invalid syntax at parsing of assignment: ";

const char ParsePrintSyntaxException::kParsePrintSyntaxMessage[] =
    "Invalid syntax at parsing of print: ";

const char ParseReadSyntaxException::kParseReadSyntaxMessage[] =
    "Invalid syntax at parsing of read: ";

const char ParseCallSyntaxException::kParseCallSyntaxMessage[] =
    "Invalid syntax at parsing of call: ";

const char ParseIfSyntaxException::kParseIfSyntaxMessage[] =
    "Invalid syntax at parsing of if: ";

const char ParseWhileSyntaxException::kParseWhileSyntaxMessage[] =
    "Invalid syntax at parsing of while: ";

const char ParseRelationSyntaxException::kParseRelationSyntaxMessage[] =
    "Invalid syntax at parsing of relation: ";

const char ParseFactorSyntaxException::kParseFactorSyntaxMessage[] =
    "Invalid syntax at parsing of factor: ";
}  // namespace sp
