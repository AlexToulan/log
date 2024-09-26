#include "Log.hpp"

#include <filesystem>
#include <fstream>
#include <mutex>
#include <iostream>

// Static member initializations
bool Log::_showInfo = false;
bool Log::_showWarn = false;
std::source_location _source;
std::mutex Log::_consoleMutex;
std::ofstream Log::_logFileStream;

Log::Log(std::source_location location) {
  _source = location;
}

void Log::init(const std::string& filePath, bool showInfo, bool showWarn) {
  if (filePath != "") {
    _logFileStream = std::ofstream(filePath, std::ofstream::trunc);
  }
  _showInfo = _showInfo;
  _showWarn = _showWarn;
}

void Log::debug(const std::string& message) {
  #ifdef DEBUG
  std::scoped_lock lock(_consoleMutex);
  std::cout << cyan() << debugTag() << reset() << " > " << message << std::endl;
  #endif
}

void Log::info(const std::string& message) {
  std::scoped_lock lock(_consoleMutex);
  if (_logFileStream.is_open()) {
    _logFileStream << infoTag() << _source.file_name() << ":" << _source.line() << " " << "> " << message << std::endl;
  }
  if (_showInfo)
  {
    std::cout << cyan() << infoTag() << blue()
      << _source.file_name() << ":" << _source.line() << std::endl << reset() << " > " << message << std::endl;
  }
}

void Log::warn(const std::string& message) {
  std::scoped_lock lock(_consoleMutex);
  if (_logFileStream.is_open()) {
    _logFileStream << warnTag() << _source.file_name() << ":" << _source.line() << " " << "> " << message << std::endl;
  }
  if (_showWarn)
  {
    std::cout << yellow() << warnTag() << blue()
      << _source.file_name() << ":" << _source.line() << std::endl << reset() << " > " << message << std::endl;
  }
}

void Log::error(const std::string& message) {
  std::scoped_lock lock(_consoleMutex);
  if (_logFileStream.is_open()) {
    _logFileStream << errorTag() << _source.file_name() << ":" << _source.line() << " " << "> " << message << std::endl;
  }
  std::cerr << red() << errorTag() << blue()
    << _source.file_name() << ":" << _source.line() << std::endl << reset() << " > " << message << std::endl;
}
