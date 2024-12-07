// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHAR_SET_STRING_UTF16_
#define _CHAR_SET_STRING_UTF16_

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
  static bool isNullString(const std::u16string &u16string);
  static bool isNullString(const std::vector<int16_t> &u16data);
  static bool isNullString(const std::vector<int16_t> &u16data,
                           const bool &isSrcLe);
  static bool isValidString(const std::u16string &u16string);
  static bool isValidString(const std::vector<int16_t> &u16data);
  static bool isValidString(const std::vector<int16_t> &u16data,
                            const bool &isSrcLe);
  static bool isValidString(const Utf16InputStream &uis, const bool &isSrcLe);
  static bool isAsciiString(const std::u16string &u16string);
  static bool isAsciiString(const std::vector<int16_t> &u16data);
  static bool isAsciiString(const std::vector<int16_t> &u16data,
                            const bool &isSrcLe);
  static bool isAsciiString(const Utf16InputStream &uis, const bool &isSrcLe);
  static std::vector<char> toU8Data(const std::u16string &u16string);
  static std::vector<char> toU8Data(const std::u16string &u16string,
                                    const bool &hasBom);
  static std::vector<char> toU8Data(const std::vector<int16_t> &u16data);
  static std::vector<char> toU8Data(const std::vector<int16_t> &u16data,
                                    const bool &isSrcLe);
  static std::vector<char> toU8Data(const std::vector<int16_t> &u16data,
                                    const bool &isSrcLe, const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::u16string &u16string);
  static std::vector<int16_t> toU16Data(const std::u16string &u16string,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::u16string &u16string,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::vector<int16_t> &u16data);
  static std::vector<int16_t> toU16Data(const std::vector<int16_t> &u16data,
                                        const bool &isSrcLe);
  static std::vector<int16_t> toU16Data(const std::vector<int16_t> &u16data,
                                        const bool &isSrcLe,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::vector<int16_t> &u16data,
                                        const bool &isSrcLe,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::u16string &u16string);
  static std::vector<int32_t> toU32Data(const std::u16string &u16string,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::u16string &u16string,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::vector<int16_t> &u16data);
  static std::vector<int32_t> toU32Data(const std::vector<int16_t> &u16data,
                                        const bool &isSrcLe);
  static std::vector<int32_t> toU32Data(const std::vector<int16_t> &u16data,
                                        const bool &isSrcLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::vector<int16_t> &u16data,
                                        const bool &isSrcLe,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::string toU8String(const std::u16string &u16string);
  static std::string toU8String(const std::vector<int16_t> &u16data);
  static std::string toU8String(const std::vector<int16_t> &u16data,
                                const bool &isSrcLe);
  static std::u16string toU16String(const std::u16string &u16string);
  static std::u16string toU16String(const std::vector<int16_t> &u16data);
  static std::u16string toU16String(const std::vector<int16_t> &u16data,
                                    const bool &isSrcLe);
  static std::u32string toU32String(const std::u16string &u16string);
  static std::u32string toU32String(const std::vector<int16_t> &u16data);
  static std::u32string toU32String(const std::vector<int16_t> &u16data,
                                    const bool &isSrcLe);
};

} // namespace String
} // namespace CharSet
} // namespace gallop
#endif