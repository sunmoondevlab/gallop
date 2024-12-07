// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHAR_SET_CHAR_CODE_UTF16_
#define _CHAR_SET_CHAR_CODE_UTF16_

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
  static bool isBom(const int16_t &charCode, const bool &isSrcLe);
  static bool isHighSurrogate(const int16_t &charCode);
  static bool isHighSurrogate(const int16_t &charCode, const bool &isSrcLe);
  static bool isLowSurrogate(const int16_t &charCode);
  static bool isLowSurrogate(const int16_t &charCode, const bool &isSrcLe);
  static bool isLineBreak(const int16_t &charCode);
  static bool isLineBreak(const int16_t &charCode, const bool &isSrcLe);
  static bool isLineFeed(const int16_t &charCode);
  static bool isLineFeed(const int16_t &charCode, const bool &isSrcLe);
  static bool isCarriageReturn(const int16_t &charCode);
  static bool isCarriageReturn(const int16_t &charCode, const bool &isSrcLe);
  static bool isAscii(const int16_t &charCode);
  static bool isAscii(const int16_t &charCode, const bool &isSrcLe);
  static bool isSurrogatePair(const int32_t &charCode);
  static bool isSurrogatePair(const int32_t &charCode, const bool &isSrcLe);
  static bool isValidCharCode(const int16_t &charCode);
  static bool isValidCharCode(const int16_t &charCode, const bool &isSrcLe);
  static bool isValidCharCode(const int16_t &charCode, const bool &isSrcLe,
                              const bool &isForString);
  static bool isValidCharCode(const int32_t &charCode);
  static bool isValidCharCode(const int32_t &charCode, const bool &isSrcLe);
  static bool isValidCharCode(const int32_t &charCode, const bool &isSrcLe,
                              const bool &isForString);
  static int16_t getBom(const bool &isDstLe);
  static int16_t getReplacementChar(const bool &isDstLe);
  static int16_t swapEndianness(const int16_t &charCode);
  static int32_t swapEndiannessSurrogatePair(const int32_t &charCode);
  static std::vector<char> toU8(const int16_t &charCode);
  static std::vector<char> toU8(const int16_t &charCode, const bool &isSrcLe);
  static std::vector<char> toU8(const int32_t &charCode);
  static std::vector<char> toU8(const int32_t &charCode, const bool &isSrcLe);
  static int32_t toU32(const int16_t &charCode);
  static int32_t toU32(const int16_t &charCode, const bool &isSrcLe);
  static int32_t toU32(const int16_t &charCode, const bool &isSrcLe,
                       const bool &isDstLe);
  static int32_t toU32(const int32_t &charCode);
  static int32_t toU32(const int32_t &charCode, const bool &isSrcLe);
  static int32_t toU32(const int32_t &charCode, const bool &isSrcLe,
                       const bool &isDstLe);
  static std::string toU8String(const int16_t &charCode);
  static std::string toU8String(const int16_t &charCode, const bool &isSrcLe);
  static std::string toU8String(const int32_t &charCode);
  static std::string toU8String(const int32_t &charCode, const bool &isSrcLe);
  static std::u16string toU16String(const int16_t &charCode);
  static std::u16string toU16String(const int16_t &charCode,
                                    const bool &isSrcLe);
  static std::u16string toU16String(const int32_t &charCode);
  static std::u16string toU16String(const int32_t &charCode,
                                    const bool &isSrcLe);
  static std::u32string toU32String(const int16_t &charCode);
  static std::u32string toU32String(const int16_t &charCode,
                                    const bool &isSrcLe);
  static std::u32string toU32String(const int32_t &charCode);
  static std::u32string toU32String(const int32_t &charCode,
                                    const bool &isSrcLe);

private:
  // BOM
  static constexpr uint16_t BomCharCode = 0xfeff;
  // replacement charcter
  static constexpr uint16_t ReplacementCharCode = 0xfffd;
  // mask
  static constexpr uint16_t MaskHighByte = 0xff00;
  static constexpr uint16_t MaskLowByte = 0x00ff;
  static constexpr uint32_t Mask1stByte = 0xff000000;
  static constexpr uint32_t Mask2ndByte = 0x00ff0000;
  static constexpr uint32_t Mask3rdByte = 0x0000ff00;
  static constexpr uint32_t Mask4thByte = 0x000000ff;
  // surrogate
  static constexpr uint16_t HighSurrogateCodeMax = 0xdb00;
  static constexpr uint16_t HighSurrogateCodeMin = 0xd800;
  static constexpr uint16_t LowSurrogateCodeMax = 0xdf00;
  static constexpr uint16_t LowSurrogateCodeMin = 0xdc00;
  // mask uint32_t
  static constexpr uint32_t MaskHighSurrogatePair = 0xffff0000;
  static constexpr uint32_t MaskLowSurrogatePair = 0x0000ffff;
  static constexpr uint32_t MaskHigh2Byte = 0xffff0000;
  static constexpr uint32_t MaskLow2Byte = 0x0000ffff;
  // shift byte
  static constexpr int SwapShiftByte = 8;
  static constexpr int ShiftLittleEndianness2Byte = 16;
  // surrogate uint32_t
  static constexpr uint32_t HighSurrogatePairMax = 0xdbff0000;
  static constexpr uint32_t HighSurrogatePairMin = 0xd8000000;
  static constexpr uint32_t LowSurrogatePairMax = 0x0000dfff;
  static constexpr uint32_t LowSurrogatePairMin = 0x0000dc00;
  // ascii
  static constexpr uint16_t AsciiByteMax = 0x007f;
  static constexpr uint16_t AsciiByteMin = 0x0000;
  // ToU32
  static constexpr uint32_t U32NonBmpCodeMin = 0x00010000;
  static constexpr int U32ShiftHighSurrogate2Byte = 16;
  static constexpr uint32_t U32ShiftHighSurrogate2Factor = 0x00000400;

  static uint16_t swapEndiannessUint(const uint16_t &charCode);
  static uint32_t swapEndiannessSurrogatePairUint(const uint32_t &charCode);
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif