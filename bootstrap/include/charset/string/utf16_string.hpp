// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_STRING_UTF16_
#define _CHARSET_STRING_UTF16_

#include "io/stream/utf16_input_stream.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace String {

using namespace gallop::IO::Stream;

class Utf16 {
public:
  Utf16() = delete;
  ~Utf16() = delete;
  static bool isNullString(const std::vector<int16_t> &u16data);
  static bool isNullString(const std::vector<int16_t> &u16data,
                           const bool &isLE);
  static bool isValidString(const std::vector<int16_t> &u16data);
  static bool isValidString(const std::vector<int16_t> &u16data,
                            const bool &isLE);
  static bool isValidString(const Utf16InputStream &uis, const bool &isLE);
  static std::vector<char> toUtf8Data(const std::vector<int16_t> &u16data);
  static std::vector<char> toUtf8Data(const std::vector<int16_t> &u16data,
                                      const bool &isLE);
  static std::vector<char> toUtf8Data(const std::vector<int16_t> &u16data,
                                      const bool &isLE, const bool &hasBom);
  static std::vector<int16_t> toUtf16Data(const std::vector<int16_t> &u16data);
  static std::vector<int16_t> toUtf16Data(const std::vector<int16_t> &u16data,
                                          const bool &isLE);
  static std::vector<int16_t> toUtf16Data(const std::vector<int16_t> &u16data,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int16_t> toUtf16Data(const std::vector<int16_t> &u16data,
                                          const bool &isLE, const bool &hasBom,
                                          const bool &isSwapEndianness);
  static std::vector<int32_t> toUtf32Data(const std::vector<int16_t> &u16data);
  static std::vector<int32_t> toUtf32Data(const std::vector<int16_t> &u16data,
                                          const bool &isLE);
  static std::vector<int32_t> toUtf32Data(const std::vector<int16_t> &u16data,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int32_t> toUtf32Data(const std::vector<int16_t> &u16data,
                                          const bool &isLE, const bool &hasBom,
                                          const bool &isSwapEndianness);
  static std::string toUtf8String(const std::vector<int16_t> &u16data);
  static std::string toUtf8String(const std::vector<int16_t> &u16data,
                                  const bool &isLE);
};

} // namespace String
} // namespace CharSet
} // namespace gallop
#endif