// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHARSET_STRING_UTF32_
#define _CHARSET_STRING_UTF32_

#include "io/stream/utf32_input_stream.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace gallop {
namespace CharSet {
namespace String {

using namespace gallop::IO::Stream;

class Utf32 {
public:
  Utf32() = delete;
  ~Utf32() = delete;
  static bool isNullString(const std::vector<int32_t> &u32data);
  static bool isNullString(const std::vector<int32_t> &u32data,
                           const bool &isLE);
  static bool isValidString(const std::vector<int32_t> &u32data);
  static bool isValidString(const std::vector<int32_t> &u32data,
                            const bool &isLE);
  static bool isValidString(const Utf32InputStream &uis, const bool &isLE);
  static std::vector<char> toUtf8Data(const std::vector<int32_t> &u32data);
  static std::vector<char> toUtf8Data(const std::vector<int32_t> &u32data,
                                      const bool &isLE);
  static std::vector<char> toUtf8Data(const std::vector<int32_t> &u32data,
                                      const bool &isLE, const bool &hasBom);
  static std::vector<int16_t> toUtf16Data(const std::vector<int32_t> &u32data);
  static std::vector<int16_t> toUtf16Data(const std::vector<int32_t> &u32data,
                                          const bool &isLE);
  static std::vector<int16_t> toUtf16Data(const std::vector<int32_t> &u32data,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int16_t> toUtf16Data(const std::vector<int32_t> &u32data,
                                          const bool &isLE, const bool &hasBom,
                                          const bool &isSwapEndianness);
  static std::vector<int32_t> toUtf32Data(const std::vector<int32_t> &u32data);
  static std::vector<int32_t> toUtf32Data(const std::vector<int32_t> &u32data,
                                          const bool &isLE);
  static std::vector<int32_t> toUtf32Data(const std::vector<int32_t> &u32data,
                                          const bool &isLE, const bool &hasBom);
  static std::vector<int32_t> toUtf32Data(const std::vector<int32_t> &u32data,
                                          const bool &isLE, const bool &hasBom,
                                          const bool &isSwapEndianness);
  static std::string toUtf8String(const std::vector<int32_t> &u32data);
  static std::string toUtf8String(const std::vector<int32_t> &u32data,
                                  const bool &isLE);
};

} // namespace String
} // namespace CharSet
} // namespace gallop
#endif