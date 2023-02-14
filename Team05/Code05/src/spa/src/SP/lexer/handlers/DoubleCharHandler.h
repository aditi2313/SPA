#include "LexerHandler.h"
#include "SP/lexer/LexerData.h"

namespace sp {
class DoubleCharHandler : public LexerHandler {
 public:
  std::optional<Token> Handle(LexerData& program) override;
};
}  // namespace sp
