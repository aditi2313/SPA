#pragma once

#include <chrono>  // NOLINT [build/c++ 11]
#include <fstream>
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
    dual_write(desc + " time: " + std::to_string(interval.count()) + " s\n");
  }

  static void EnterSection(std::string desc) {
    if (disabled_) return;
    times_.push(Clock::now());
    times_.push(Clock::now());
    dual_write(kSection + "Enter Section: " + desc + kSection + "\n");
  }

  static void ExitSection(std::string desc) {
    if (disabled_) return;
    times_.pop();
    auto curr = Clock::now();
    Duration interval = curr - times_.top();
    times_.pop();
    dual_write(kSection + "Exit Section: " + desc + " With interval: "
               + std::to_string(interval.count()) + kSection + "\n");
  }

  // Used to separate runs to easily see in the log output
  static void PrintDivider() {
    dual_write(kDivider);
  }

 private:
  inline static bool disabled_ = false;
  inline static std::stack<Clock::time_point> times_;
  inline static std::string kSection = " <===========================> ";
  inline static std::string kDivider = "\n----\n\n";

  // Writes to stdout and a log file
  static void dual_write(const std::string& str) {
    // autotester_path_mac = ../Code05/cmake-build-debug/src/autotester
    // autotester_path_windows = ../Code05/out/build/x64-Debug/src/autotester
    std::string logger_path;
    #ifdef _WIN32
        logger_path = "..\\..\\..\\..\\..\\..\\Tests05\\logging_output.txt";
    #else
        logger_path = "../../../../Tests05/logging_output.txt";
    #endif
        std::filesystem::path cwd = std::filesystem::current_path();
        std::filesystem::path output_path = cwd / logger_path;

    std::ofstream out_file(output_path.c_str(), std::ios_base::app);
    out_file << str;
    std::cout << str;
  }
};

}  // namespace logging
