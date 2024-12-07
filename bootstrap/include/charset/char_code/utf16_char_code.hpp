// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_CHAR_CODE_UTF16_
#define _CHARSET_CHAR_CODE_UTF16_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace CharCode {

class Utf16 {
public:
  Utf16() = delete;
  ~Utf16() = delete;
  static bool isNullCharCode(const int16_t &charCode);
  static bool isBom(const int16_t &charCode);
  static bool isBom(const int16_t &charCode, const bool &isLE);
  static bool isHighSurrogate(const int16_t &charCode);
  static bool isHighSurrogate(const int16_t &charCode, const bool &isLE);
  static bool isLowSurrogate(const int16_t &charCode);
  static bool isLowSurrogate(const int16_t &charCode, const bool &isLE);
  static bool isNewLine(const int16_t &charCode);
  static bool isNewLine(const int16_t &charCode, const bool &isLE);
  static bool isAscii(const int16_t &charCode);
  static bool isAscii(const int16_t &charCode, const bool &isLE);
  static bool isSurrogatePair(const int32_t &charCode);
  static bool isSurrogatePair(const int32_t &charCode, const bool &isLE);
  static int16_t swapEndianness(const int16_t &charCode);
  static int32_t swapEndiannessSurrogatePair(const int32_t &charCode);
  static int32_t toUtf32(const int16_t &charCode);
  static int32_t toUtf32(const int16_t &charCode, const bool &isLE);
  static int32_t toUtf32(const int16_t &charCode, const bool &isLE,
                         const bool &isSwapEndianness);
  static int32_t toUtf32(const int32_t &charCode);
  static int32_t toUtf32(const int32_t &charCode, const bool &isLE);
  static int32_t toUtf32(const int32_t &charCode, const bool &isLE,
                         const bool &isSwapEndianness);
  static std::vector<char> toUtf8Chunk(const int16_t &charCode);
  static std::vector<char> toUtf8Chunk(const int16_t &charCode,
                                       const bool &isLE);
  static std::vector<char> toUtf8Chunk(const int32_t &charCode);
  static std::vector<char> toUtf8Chunk(const int32_t &charCode,
                                       const bool &isLE);
  static std::string toString(const int16_t &charCode);
  static std::string toString(const int16_t &charCode, const bool &isLE);
  static std::string toString(const int32_t &charCode);
  static std::string toString(const int32_t &charCode, const bool &isLE);
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif