// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_CHAR_CODE_UTF8_
#define _CHARSET_CHAR_CODE_UTF8_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace CharCode {

class Utf8 {
public:
  Utf8() = delete;
  ~Utf8() = delete;
  static bool isNullCharCode(const int8_t &charCode);
  static bool isBom(const int32_t &charCode);
  static int32_t utf8FetchLength(const int8_t &charCode);
  static bool isContinuationByte(const int8_t &charCode);
  static bool isNewLine(const int8_t &charCode);
  static bool isAscii(const int8_t &charCode);
  static bool isValidCharCode(const int32_t &charCode);
  static int32_t toUtf32(const int32_t &charCode);
  static int32_t toUtf32(const int32_t &charCode, const bool &isLE);
  static std::vector<int16_t> toUtf16Chunk(const int32_t &charCode);
  static std::vector<int16_t> toUtf16Chunk(const int32_t &charCode,
                                           const bool &isLE);
  static std::vector<char> toUtf8Chunk(const int32_t &charCode);
  static std::string toString(const int32_t &charCode);
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif