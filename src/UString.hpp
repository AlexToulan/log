#pragma once
#include <string>
#include <sstream>
#include <iostream>

/// @brief String manipulation utilities
class UString
{
public:
  /// @brief Concatenates a parameter pack with a string stream
  /// @tparam ...VArgs Variadic template arguments
  /// @param ...vargs Parameter pack to be concatenated
  /// @return The concatenated string
  template<typename... VArgs>
  static std::string concat(VArgs&&... vargs) {
    std::ostringstream ss;
    _concat(ss, std::forward<VArgs>(vargs)...);
    return ss.str();
  }

  /// @brief Formats a string with variadic arguments
  /// @tparam ...VArgs Variadic template arguments
  /// @param format The format string
  /// @param ...vargs Argument pack to be formatted into the string
  /// @return The formatted string
  template<typename... VArgs>
  static std::string format(const std::string& format, VArgs&&... vargs) {
    std::string out;
    _format(out, format, std::forward<VArgs>(vargs)...);
    return out;
  }

private:
  /// @brief Helper function to concatenate elements into a string stream
  /// @tparam T The type of the element to be added
  /// @tparam ...VArgs Variadic template arguments for additional elements
  /// @param ss The string stream to which elements are appended
  /// @param t The first element to add
  /// @param vargs Additional elements to add
  template<typename T, typename... VArgs>
  static void _concat(std::ostringstream& ss, T t, VArgs&&... vargs) {
    ss << t;
    if constexpr (sizeof...(vargs) > 0) {
        _concat(ss, std::forward<VArgs>(vargs)...);
    }
  }

  /// @brief Helper function to format elements into a string
  /// @tparam T The type of the element to be added
  /// @tparam ...VArgs Variadic template arguments for additional elements
  /// @param out The resulting string that is being built
  /// @param format The format string containing placeholders
  /// @param t The first element to add
  /// @param vargs Additional elements to add
  template<typename T, typename... VArgs>
  static void _format(std::string& out, const std::string& format, T t, VArgs&&... vargs) {
    if (_format(out, format, t)) {
      _format(out, format, std::forward<VArgs>(vargs)...);
    }
  }

  /// @brief Formats a single element into the output string and updates the format string to remove used placeholder
  /// @tparam T The type of the element to be added
  /// @param out The resulting string that is being built
  /// @param format The format string containing placeholders
  /// @param t The first element to add
  template<typename T>
  static bool _format(std::string& out, const std::string& format, T t) {
    size_t pos = format.find("{}");
    if (pos == std::string::npos) {
      out += format;
      return false;
    } else {
      out += format.substr(0, pos);
      std::ostringstream oss;
      oss << t;
      out += oss.str();
      return true;
    }
  }
};
