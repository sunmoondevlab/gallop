// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _UTIL_HEXSTRINGER_HEXSTRINGER_
#define _UTIL_HEXSTRINGER_HEXSTRINGER_

#include <cstdint>
#include <string>
#include <vector>

namespace gallop {
namespace Util {
class HexStringer {
public:
  static std::string dumpChar(const char &binData);
  static std::string dumpChar(const uint8_t &binData);
  static std::string dumpChar(const uint8_t &binData, const bool &isFixZero);

  static std::string dumpChar(const int16_t &binData);
  static std::string dumpChar(const int16_t &binData, const bool &isFixZero);
  static std::string dumpChar(const int16_t &binData, const bool &isFixZero,
                              const bool &isOmitSpace);
  static std::string dumpChar(const uint16_t &binData);
  static std::string dumpChar(const uint16_t &binData, const bool &isFixZero);
  static std::string dumpChar(const uint16_t &binData, const bool &isFixZero,
                              const bool &isOmitSpace);

  static std::string dumpChar(const int32_t &binData);
  static std::string dumpChar(const int32_t &binData, const bool &isFixZero);
  static std::string dumpChar(const int32_t &binData, const bool &isFixZero,
                              const bool &isOmitSpace);
  static std::string dumpChar(const uint32_t &binData);
  static std::string dumpChar(const uint32_t &binData, const bool &isFixZero);
  static std::string dumpChar(const uint32_t &binData, const bool &isFixZero,
                              const bool &isOmitSpace);

  static std::string dumpChar(const int64_t &binData);
  static std::string dumpChar(const uint64_t &binData);

  static std::string dumpString(const std::string &str);
  static std::string dumpString(const std::vector<char> &str);

  static std::string codeGenVector(const std::string &str);
  static std::string codeGenVector(const std::vector<char> &str);
  static std::string codeGenVector(const std::u16string &str);
  static std::string codeGenVector(const std::vector<int16_t> &str);
  static std::string codeGenVector(const std::u32string &str);
  static std::string codeGenVector(const std::vector<int32_t> &str);

private:
  // shift for toU8
  static constexpr uint8_t MaskChar = 0xff;
  // shift for toU8
  static constexpr int ByteShift7 = 56;
  static constexpr int ByteShift6 = 48;
  static constexpr int ByteShift5 = 40;
  static constexpr int ByteShift4 = 32;
  static constexpr int ByteShift3 = 24;
  static constexpr int ByteShift2 = 16;
  static constexpr int ByteShift1 = 8;
};
} // namespace Util
} // namespace gallop
#endif