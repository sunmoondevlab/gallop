// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_CHAR_CODE_UTF32_
#define _CHARSET_CHAR_CODE_UTF32_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace CharCode {

class Utf32 {
public:
  Utf32() = delete;
  ~Utf32() = delete;
  static bool isNullCharCode(const int32_t &charCode);
  static bool isBom(const int32_t &charCode);
  static bool isBom(const int32_t &charCode, const bool &isLE);
  static bool isNewLine(const int32_t &charCode);
  static bool isNewLine(const int32_t &charCode, const bool &isLE);
  static bool isAscii(const int32_t &charCode);
  static bool isAscii(const int32_t &charCode, const bool &isLE);
  static bool isValidCharCode(const int32_t &charCode);
  static bool isValidCharCode(const int32_t &charCode, const bool &isLE);
  static int32_t swapEndianness(const int32_t &charCode);
  static std::vector<char> toUtf8Chunk(const int32_t &charCode);
  static std::vector<char> toUtf8Chunk(const int32_t &charCode,
                                       const bool &isLE);
  static std::string toString(const int32_t &charCode);
  static std::string toString(const int32_t &charCode, const bool &isLE);
  static std::vector<int16_t> toUtf16Chunk(const int32_t &charCode);
  static std::vector<int16_t> toUtf16Chunk(const int32_t &charCode,
                                           const bool &isLE);
  static std::vector<int16_t> toUtf16Chunk(const int32_t &charCode,
                                           const bool &isLE,
                                           const bool &isSwapEndianness);
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif