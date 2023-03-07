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
  static void ResetClock() {
    if (disabled_) return;
    if (!times_.empty()) times_.pop();
    times_.push(Clock::now());
  }

  // TODO(Gab) consider removal of desc as it creates unnecessary overhead

  /// <summary>
  /// Function writes the interval from the previous log,
  /// or the previous reset, or the start of the current section
  /// as well as the provided description into the log.
  /// </summary>
  /// <param name="desc"></param>
  static void LogAndStop(std::string desc) {
    if (disabled_) return;
    Clock::time_point curr = Clock::now();
    Duration interval = curr - times_.top();
    times_.pop();
    times_.push(curr);
    std::cout << desc << " time: " << interval.count() << " s" << std::endl;
  }

  static void EnterSection(std::string desc) {
    if (disabled_) return;
    times_.push(Clock::now());
    times_.push(Clock::now());
    std::cout << kSection << "Enter Section: " << desc << kSection << std::endl;
  }

  static void ExitSection(std::string desc) {
    if (disabled_) return;
    times_.pop();
    auto curr = Clock::now();
    Duration interval = curr - times_.top();
    times_.pop();
    std::cout << kSection << "Exit Section: " << desc
              << " With interval: " << interval.count() << kSection
              << std::endl;
  }

 private:
  inline static bool disabled_ = false;
  inline static std::stack<Clock::time_point> times_;
  inline static const char kSection[] = " <===========================> ";
};

}  // namespace logging
