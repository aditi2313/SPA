#include "LexerHandler.h"

namespace sp {
class DoubleCharHandler : public LexerHandler {
 protected:
  std::optional<Token> HandleInner(int& ptr, std::string& program) override;
};
}  // namespace sp