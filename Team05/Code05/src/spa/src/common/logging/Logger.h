#pragma once

#include <chrono>  // NOLINT [build/c++ 11]
#include <iostream>
#include <stack>
#include <string>

using Clock = std::chrono::system_clock;
using Duration = std::chrono::duration<double>;

namespace logging {
/// <summary>
/// Singleton logger for logging.
/// </summary>
class Logger {
 public:
  static void Start() {
    if (disabled) return;
    times_.push(Clock::now());
  }

  // TODO(Gab) consider removal of desc as it creates unnecessary overhead
  static void LogAndStop(std::string desc) {
    if (disabled) return;
    auto curr = Clock::now();
    std::chrono::duration<double> interval = curr - times_.top();
    std::cout << desc << " time: " << interval.count() << " s" << std::endl;
    times_.pop();
  }

 private:
  inline static bool disabled = false;
  inline static std::stack<Clock::time_point> times_;
};

}  // namespace logging
