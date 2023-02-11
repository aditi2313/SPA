#pragma once

namespace sp {
class Token {
 public:
  virtual bool IsStmt { return false; }
  virtual bool IsProcedure { return false; }
  virtual bool IsComparison { return false; }
  virtual bool IsLogical { return false; }
  virtual bool IsBracket { return false; }
  virtual bool IsCurly { return false; 
  virtual bool IsOpen { return false; }
  };

}  // namespace sp