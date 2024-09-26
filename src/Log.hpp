#pragma once

#include "UString.hpp"

#include <source_location>
#include <string>
#include <mutex>
#include <ofstream>
#include <iostream>

/// @brief Provides thread-safe methods for logging messages at different levels to the console and optionally a file.
class Log {
public:
  /// @brief Constructor that captures the source location used for logging
  Log(std::source_location location = std::source_location::current());
  Log(const Log& other) = delete;
  Log(Log&& other) = delete;
  Log operator=(const Log& other) = delete;

  /// @brief Static initialization method for the log file
  static void init(const std::string& filePath, bool showInfo, bool showWarn);

  // Log methods with different levels
  void debug(const std::string& message);
  template <typename ... VArgs>
  void debug(const std::string_view& format, VArgs... vargs) {
    debug(UString::format(format, vargs...));
  }
  
  void info(const std::string& message);
  template <typename ... VArgs>
  void info(const std::string_view& format, VArgs... vargs) {
    info(UString::format(format, vargs...));
  }

  void warn(const std::string& message);
  template <typename ... VArgs>
  void warn(const std::string_view& format, VArgs... vargs) {
    warn(UString::format(format, vargs...));
  }

  void error(const std::string& message);
  template <typename ... VArgs>
  void error(const std::string_view& format, VArgs... vargs) {
    error(UString::format(format, vargs...));
  }

private:
  // Static members for log levels and file stream
  static bool _showInfo;
  static bool _showWarn;

  std::source_location _source;
  static std::mutex _consoleMutex;
  static std::ofstream _logFileStream;

  // Category tags for different log levels
  static const std::string& debugTag() { return std::string("[  DEBUG  ] "); };
  static const std::string& infoTag()  { return std::string("[  INFO   ] "); };
  static const std::string& warnTag()  { return std::string("[ WARNING ] "); };
  static const std::string& errorTag() { return std::string("[  ERROR  ] "); };

  // Color codes for console output 
  static const std::string& red() { return std::string("\033[0;31m"); };
  static const std::string& green() { return std::string("\033[1;32m"); };
  static const std::string& yellow() { return std::string("\033[1;33m"); };
  static const std::string& blue() { return std::string("\033[1;34m"); };
  static const std::string& cyan() { return std::string("\033[0;36m"); };
  static const std::string& magenta() { return std::string("\033[0;35m"); };
  static const std::string& reset() { return std::string("\033[0m"); };
};
