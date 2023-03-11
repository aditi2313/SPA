#pragma once

#include <functional>
#include <string>

namespace qps {
class Grammar {
 public:
  using CheckLambda = std::function<bool(std::string)>;

  Grammar(
      std::function<bool(std::string)> check,
      std::function<void()> action)
      : check_(check), action_(action) {}

  static std::function<bool(std::string)> kArgumentCheck;
  static std::function<bool(std::string)> kBooleanCheck;
  static std::function<bool(std::string)> kDesignEntityCheck;
  static std::function<bool(std::string)> kElemCheck;
  static std::function<bool(std::string)> kExprCheck;
  static std::function<bool(std::string)> kRefCheck;
  static std::function<bool(std::string)> kRelRefCheck;
  static std::function<bool(std::string)> kSelectCheck;
  static std::function<bool(std::string)> kSynCheck;
  static std::function<bool(std::string)> kTupleCheck;

  inline bool Check(std::string token) {
    return check_(token);
  }

  inline void Action() {
    action_();
  }
 private:
  CheckLambda check_;
  std::function<void()> action_;
};
}
