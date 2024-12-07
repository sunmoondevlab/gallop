// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHAR_SET_STRING_UTF8_
#define _CHAR_SET_STRING_UTF8_

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
  static bool isValidString(const Utf8InputStream &uis);
  static bool isAsciiString(const std::string &u8string);
  static bool isAsciiString(const std::vector<char> &u8data);
  static bool isAsciiString(const Utf8InputStream &uis);
  static std::vector<char> toU8Data(const std::string &u8string);
  static std::vector<char> toU8Data(const std::string &u8string,
                                    const bool &hasBom);
  static std::vector<char> toU8Data(const std::vector<char> &u8data);
  static std::vector<char> toU8Data(const std::vector<char> &u8data,
                                    const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::string &u8string);
  static std::vector<int16_t> toU16Data(const std::string &u8string,
                                        const bool &isDstLe);
  static std::vector<int16_t> toU16Data(const std::string &u8string,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int16_t> toU16Data(const std::vector<char> &u8data);
  static std::vector<int16_t> toU16Data(const std::vector<char> &u8data,
                                        const bool &isDstLe);
  static std::vector<int16_t> toU16Data(const std::vector<char> &u8data,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::string &u8string);
  static std::vector<int32_t> toU32Data(const std::string &u8string,
                                        const bool &isDstLe);
  static std::vector<int32_t> toU32Data(const std::string &u8string,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::vector<int32_t> toU32Data(const std::vector<char> &u8data);
  static std::vector<int32_t> toU32Data(const std::vector<char> &u8data,
                                        const bool &isDstLe);
  static std::vector<int32_t> toU32Data(const std::vector<char> &u8data,
                                        const bool &isDstLe,
                                        const bool &hasBom);
  static std::string toU8String(const std::string &u8string);
  static std::string toU8String(const std::vector<char> &u8data);
  static std::u16string toU16String(const std::string &u8string);
  static std::u16string toU16String(const std::vector<char> &u8data);
  static std::u32string toU32String(const std::string &u8string);
  static std::u32string toU32String(const std::vector<char> &u8data);
};

} // namespace String
} // namespace CharSet
} // namespace gallop
#endif