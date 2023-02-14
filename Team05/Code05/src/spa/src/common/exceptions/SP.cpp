#include "SP.h"

namespace sp {

const char LexerException::kLexerExceptionMessage[] =
    "Exception occured at Lexer: ";
const char ParseRelationSyntaxException::kParseRelationSyntaxMessage[] =
    "Invalid syntax at parsing of relation";

const char ParseFactorSyntaxException::kParseFactorSyntaxMessage[] =
    "Invalid syntax at parsing of factor";
}  // namespace sp
