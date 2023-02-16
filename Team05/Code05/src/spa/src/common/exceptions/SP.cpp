#include "SP.h"

namespace sp {

void AssertExpectedToken(Token to_test, Token expected, std::string token) {
  if (to_test != expected) {
    throw ParseException("Wrong token received: " + token);
  }
}

const char LexerException::kLexerExceptionMessage[] =
    "Exception occured at Lexer: ";
const char ParseRelationSyntaxException::kParseRelationSyntaxMessage[] =
    "Invalid syntax at parsing of relation";

const char ParseFactorSyntaxException::kParseFactorSyntaxMessage[] =
    "Invalid syntax at parsing of factor";
}  // namespace sp
