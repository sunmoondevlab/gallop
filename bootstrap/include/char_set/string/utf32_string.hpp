// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHAR_SET_STRING_UTF32_
#define _CHAR_SET_STRING_UTF32_

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
  static bool isNullString(const std::u32string &u32string);
  static bool isNullString(const std::vector<int32_t> &u32data);
  static bool isNullString(const std::vector<int32_t> &u32data,
                           const bool &isSrcLe);
  static bool isValidString(const std::u32string &u32string);
  static bool isValidString(const std::vector<int32_t> &u32data);
  static bool isValidString(const std::vector<int32_t> &u32data,
                            const bool &isSrcLe);
  static bool isValidString(const Utf32InputStream &uis, const bool &isSrcLe);
  static bool isAsciiString(const std::u32string &u32string);
  static bool isAsciiString(const std::vector<int32_t> &u32data);
  static bool isAsciiString(const std::vector<int32_t> &u32data,
                            const bool &isSrcLe);
  static bool isAsciiString(const Utf32InputStream &uis, const bool &isSrcLe);
  static std::vector<char> toU8Data(const std::u32string &u32string);
  static std::vector<char> toU8Data(const std::u32string &u32string,
                                    const bool &hasBom);
  static std::vector<char> toU8Data(const std::vector<int32_t> &u32data);
  static std::vector<char> toU8Data(const std::vector<int32_t> &u32data,
                                    const bool &isSrcLe);
  static std::vector<char> toU8Data(const std::vector<int32_t> &u32data,
                                    const bool &isSrcLe, const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::u32string &u32string);
  static std::vector<int16_t> toU16Data(const std::u32string &u32string,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::u32string &u32string,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::vector<int32_t> &u32data);
  static std::vector<int16_t> toU16Data(const std::vector<int32_t> &u32data,
                                        const bool &isSrcLe);
  static std::vector<int16_t> toU16Data(const std::vector<int32_t> &u32data,
                                        const bool &isSrcLe,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::vector<int32_t> &u32data,
                                        const bool &isSrcLe,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::u32string &u32string);
  static std::vector<int32_t> toU32Data(const std::u32string &u32string,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::u32string &u32string,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::vector<int32_t> &u32data);
  static std::vector<int32_t> toU32Data(const std::vector<int32_t> &u32data,
                                        const bool &isSrcLe);
  static std::vector<int32_t> toU32Data(const std::vector<int32_t> &u32data,
                                        const bool &isSrcLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::vector<int32_t> &u32data,
                                        const bool &isSrcLe,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::string toU8String(const std::u32string &u32string);
  static std::string toU8String(const std::vector<int32_t> &u32data);
  static std::string toU8String(const std::vector<int32_t> &u32data,
                                const bool &isSrcLe);
  static std::u16string toU16String(const std::u32string &u32string);
  static std::u16string toU16String(const std::vector<int32_t> &u32data);
  static std::u16string toU16String(const std::vector<int32_t> &u32data,
                                    const bool &isSrcLe);
  static std::u32string toU32String(const std::u32string &u32string);
  static std::u32string toU32String(const std::vector<int32_t> &u32data);
  static std::u32string toU32String(const std::vector<int32_t> &u32data,
                                    const bool &isSrcLe);
};

} // namespace String
} // namespace CharSet
} // namespace gallop
#endif