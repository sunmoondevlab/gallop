// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#ifndef _CHAR_SET_CHAR_CODE_UTF32_
#define _CHAR_SET_CHAR_CODE_UTF32_

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
  static bool isBom(const int32_t &charCode, const bool &isSrcLe);
  static bool isLineBreak(const int32_t &charCode);
  static bool isLineBreak(const int32_t &charCode, const bool &isSrcLe);
  static bool isLineFeed(const int32_t &charCode);
  static bool isLineFeed(const int32_t &charCode, const bool &isSrcLe);
  static bool isCarriageReturn(const int32_t &charCode);
  static bool isCarriageReturn(const int32_t &charCode, const bool &isSrcLe);
  static bool isAscii(const int32_t &charCode);
  static bool isAscii(const int32_t &charCode, const bool &isSrcLe);
  static bool isValidCharCode(const int32_t &charCode);
  static bool isValidCharCode(const int32_t &charCode, const bool &isSrcLe);
  static int32_t getBom(const bool &isDstLe);
  static int32_t getReplacementChar(const bool &isDstLe);
  static int32_t swapEndianness(const int32_t &charCode);
  static std::vector<char> toU8(const int32_t &charCode);
  static std::vector<char> toU8(const int32_t &charCode, const bool &isSrcLe);
  static std::vector<int16_t> toU16(const int32_t &charCode);
  static std::vector<int16_t> toU16(const int32_t &charCode,
                                    const bool &isSrcLe);
  static std::vector<int16_t> toU16(const int32_t &charCode,
                                    const bool &isSrcLe, const bool &isDstLe);
  static std::string toU8String(const int32_t &charCode);
  static std::string toU8String(const int32_t &charCode, const bool &isSrcLe);
  static std::u16string toU16String(const int32_t &charCode);
  static std::u16string toU16String(const int32_t &charCode,
                                    const bool &isSrcLe);
  static std::u32string toU32String(const int32_t &charCode);
  static std::u32string toU32String(const int32_t &charCode,
                                    const bool &isSrcLe);
  static bool isSpaceChar(const int32_t &charCode);
  static bool isNumberChar(const int32_t &charCode);
  static bool isUpperAlphaChar(const int32_t &charCode);
  static bool isLowerAlphaChar(const int32_t &charCode);
  static bool isAlphabetChar(const int32_t &charCode);
  static bool isAlphabetNumberChar(const int32_t &charCode);
  static bool isSymbolChar(const int32_t &charCode);
  static bool isIdentifierChar(const int32_t &charCode);
  static bool isIdentifierChar(const int32_t &charCode, const bool &isContinue);
  static bool isBinaryDigitChar(const int32_t &charCode);
  static bool isBinaryDigitChar(const int32_t &charCode,
                                const bool &isForNumberLiteral);
  static bool isOctalDigitChar(const int32_t &charCode);
  static bool isOctalDigitChar(const int32_t &charCode,
                               const bool &isForNumberLiteral);
  static bool isDecimalDigitChar(const int32_t &charCode);
  static bool isDecimalDigitChar(const int32_t &charCode,
                                 const bool &isForNumberLiteral);
  static bool isHexadecimalDigitChar(const int32_t &charCode);
  static bool isHexadecimalDigitChar(const int32_t &charCode,
                                     const bool &isForNumberLiteral);
  static bool isDigitCharByRadix(const int32_t &charCode, const uint8_t radix);
  static bool isDigitCharByRadix(const int32_t &charCode, const uint8_t radix,
                                 const bool &isForNumberLiteral);
  static bool isDigitCharByRadix(const int32_t &charCode, const uint8_t radix,
                                 const bool &isLowerPrefer,
                                 const bool &isForNumberLiteral);
  static bool equalsCharIgnoreCase(const int32_t &charCode,
                                   const int32_t &expectCharCode);
  static int32_t toDecimalFromBinaryChar(const int32_t &charCode);
  static int32_t toDecimalFromOctalChar(const int32_t &charCode);
  static int32_t toDecimalFromDecimalChar(const int32_t &charCode);
  static int32_t toDecimalFromHexadecimalChar(const int32_t &charCode);
  static int32_t toDecimalFromDigitCharByRadix(const int32_t &charCode,
                                               const uint8_t radix);
  static int32_t toDecimalFromDigitCharByRadix(const int32_t &charCode,
                                               const uint8_t radix,
                                               const bool &isLowerPrefer);
  static int32_t toBinaryCharFromDecimal(const int32_t &digit);
  static int32_t toOctalCharFromDecimal(const int32_t &digit);
  static int32_t toDecimalCharFromDecimal(const int32_t &digit);
  static int32_t toHexadecimalCharFromDecimal(const int32_t &digit);
  static int32_t toHexadecimalCharFromDecimal(const int32_t &digit,
                                              const bool &isLowerPrefer);
  static int32_t toDigitCharFromDecimalByRadix(const int32_t &digit,
                                               const uint8_t radix);
  static int32_t toDigitCharFromDecimalByRadix(const int32_t &digit,
                                               const uint8_t radix,
                                               const bool &isLowerPrefer);

private:
  // BOM
  static constexpr uint32_t BomCharCode = 0x0000feff;
  // replacement charcter
  static constexpr uint32_t ReplacementCharCode = 0x0000fffd;
  // ascii
  static constexpr uint32_t AsciiByteMax = 0x0000007f;
  static constexpr uint32_t AsciiByteMin = 0x00000000;
  // CodePoint
  static constexpr uint32_t CodePointMax = 0x0010ffff;
  static constexpr uint32_t CodePointMin = 0x00000000;
  static constexpr uint32_t CodePoint4ByteU8Min = 0x00010000;
  static constexpr uint32_t CodePoint3ByteU8Min = 0x00000800;
  static constexpr uint32_t CodePoint2ByteU8Min = 0x00000080;
  // ToU16
  static constexpr uint16_t U16MaskHighByte = 0xff00;
  static constexpr uint16_t U16MaskLowByte = 0x00ff;
  // surrogate
  static constexpr uint16_t U16HighSurrogateCodeMin = 0xd800;
  static constexpr uint16_t U16LowSurrogateCodeMin = 0xdc00;
  static constexpr uint32_t SurrogateCodeMax = 0x0000dfff;
  static constexpr uint32_t SurrogateCodeMin = 0x0000d800;
  // mask
  static constexpr uint32_t Mask1stByte = 0xff000000;
  static constexpr uint32_t Mask2ndByte = 0x00ff0000;
  static constexpr uint32_t Mask3rdByte = 0x0000ff00;
  static constexpr uint32_t Mask4thByte = 0x000000ff;
  // shift byte
  static constexpr int SwapShiftOuterByte = 24;
  static constexpr int SwapShiftInnerByte = 8;
  // toU8
  static constexpr uint8_t FlagHighestChar4Byte = 0xf0;
  static constexpr uint8_t FlagHighestChar3Byte = 0xe0;
  static constexpr uint8_t FlagHighestChar2Byte = 0xc0;
  static constexpr uint8_t FlagContinuation2Byte = 0x80;
  static constexpr uint8_t MaskContinuationByte = 0x3f;
  static constexpr int Shift1stByte = 18;
  static constexpr int Shift2ndByte = 12;
  static constexpr int Shift3rdByte = 6;
  // U16
  static constexpr uint32_t U32DivideHighSurrogate2Factor = 0x00000400;

  static constexpr uint8_t MinRadix = 2;
  static constexpr uint8_t MaxRadix = 62;
  static constexpr uint8_t NumOnlyMaxRadix = 10;
  static constexpr uint8_t CiAlphabetNumMaxRadix = 36;
  static constexpr uint8_t CiAlphabetNumMinRadix = 11;
  static constexpr uint8_t CsAlphabetNumMinRadix = 37;

  static uint32_t swapEndiannessUint(const uint32_t &charCode);
};

} // namespace CharCode
} // namespace CharSet
} // namespace gallop
#endif