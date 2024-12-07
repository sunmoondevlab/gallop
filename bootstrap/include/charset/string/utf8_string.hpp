// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_STRING_UTF8_
#define _CHARSET_STRING_UTF8_

#include "io/stream/utf8_input_stream.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

using namespace gallop::IO::Stream;

namespace gallop {
namespace CharSet {
namespace String {

class Utf8 {
public:
  Utf8() = delete;
  ~Utf8() = delete;
  static bool isNullString(const std::string &u8string);
  static bool isNullString(const std::vector<char> &u8data);
  static bool isValidString(const std::string &u8string);
  static bool isValidString(const std::vector<char> &u8data);
  static bool isValidString(const Utf8InputStream &bais);
  static bool isAsciiString(const std::string &u8string);
  static bool isAsciiString(const std::vector<char> &u8data);
  static bool isAsciiString(const Utf8InputStream &bais);
  static std::vector<char> toUtf8Data(const std::string &u8string);
  static std::vector<char> toUtf8Data(const std::string &u8string,
                                      const bool &hasBom);
  static std::vector<char> toUtf8Data(const std::vector<char> &u8data);
  static std::vector<char> toUtf8Data(const std::vector<char> &u8data,
                                      const bool &hasBom);
  static std::vector<int16_t> toUtf16Data(const std::string &u8string);
  static std::vector<int16_t> toUtf16Data(const std::string &u8string,
                                          const bool &isLE);
  static std::vector<int16_t> toUtf16Data(const std::string &u8string,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int16_t> toUtf16Data(const std::vector<char> &u8data);
  static std::vector<int16_t> toUtf16Data(const std::vector<char> &u8data,
                                          const bool &isLE);
  static std::vector<int16_t> toUtf16Data(const std::vector<char> &u8data,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int32_t> toUtf32Data(const std::string &u8string);
  static std::vector<int32_t> toUtf32Data(const std::string &u8string,
                                          const bool &isLE);
  static std::vector<int32_t> toUtf32Data(const std::string &u8string,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int32_t> toUtf32Data(const std::vector<char> &u8data);
  static std::vector<int32_t> toUtf32Data(const std::vector<char> &u8data,
                                          const bool &isLE);
  static std::vector<int32_t> toUtf32Data(const std::vector<char> &u8data,
                                          const bool &isLE, const bool &hasBom);
  static std::string toUtf8String(const std::string &u8string);
  static std::string toUtf8String(const std::vector<char> &u8data);
};

} // namespace String
} // namespace CharSet
} // namespace gallop
#endif