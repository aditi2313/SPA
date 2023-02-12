#include "models/tokens/Token.h"

namespace sp {
class ProcedureToken : public Token {
 public:
  inline bool IsProcedure() override { return true; }
};
}  // namespace sp