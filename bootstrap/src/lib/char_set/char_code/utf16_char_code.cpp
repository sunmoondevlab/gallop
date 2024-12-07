// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/char_code/utf16_char_code.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"

using namespace gallop::CharSet::CharCode;

bool Utf16::isNullCharCode(const int16_t &charCode_) { return charCode_ == 0; };
bool Utf16::isBom(const int16_t &charCode_) { return isBom(charCode_, false); };
bool Utf16::isBom(const int16_t &charCode_, const bool &isSrcLe_) {
  uint16_t charCode = (uint16_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // bom
  return charCode == BomCharCode;
};
bool Utf16::isHighSurrogate(const int16_t &charCode_) {
  return isHighSurrogate(charCode_, false);
};
bool Utf16::isHighSurrogate(const int16_t &charCode_, const bool &isSrcLe_) {
  uint16_t charCode = (uint16_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // U+D800　〜　U+DBFF
  uint16_t surrogate = charCode & MaskHighByte;
  return HighSurrogateCodeMin <= surrogate && surrogate <= HighSurrogateCodeMax;
};
bool Utf16::isLowSurrogate(const int16_t &charCode_) {
  return isLowSurrogate(charCode_, false);
};
bool Utf16::isLowSurrogate(const int16_t &charCode_, const bool &isSrcLe_) {
  uint16_t charCode = (uint16_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // U+DC00　〜　U+DFFF
  uint16_t surrogate = charCode & MaskHighByte;
  return LowSurrogateCodeMin <= surrogate && surrogate <= LowSurrogateCodeMax;
};
bool Utf16::isLineBreak(const int16_t &charCode_) {
  return isLineBreak(charCode_, false);
};
bool Utf16::isLineBreak(const int16_t &charCode_, const bool &isSrcLe_) {
  // U+000A　,　U+000D
  return isLineFeed(charCode_, isSrcLe_) ||
         isCarriageReturn(charCode_, isSrcLe_);
};
bool Utf16::isLineFeed(const int16_t &charCode_) {
  return isLineFeed(charCode_, false);
};
bool Utf16::isLineFeed(const int16_t &charCode_, const bool &isSrcLe_) {
  uint16_t charCode = (uint16_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // U+000A
  return charCode == static_cast<uint16_t>(UtfAsciiTable::LineFeed);
};
bool Utf16::isCarriageReturn(const int16_t &charCode_) {
  return isCarriageReturn(charCode_, false);
};
bool Utf16::isCarriageReturn(const int16_t &charCode_, const bool &isSrcLe_) {
  uint16_t charCode = (uint16_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // 　U+000D
  return charCode == static_cast<uint16_t>(UtfAsciiTable::CarriageReturn);
};
bool Utf16::isAscii(const int16_t &charCode_) {
  return isAscii(charCode_, false);
};
bool Utf16::isAscii(const int16_t &charCode_, const bool &isSrcLe_) {
  uint16_t charCode = (uint16_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  return AsciiByteMin <= charCode && charCode <= AsciiByteMax;
};
bool Utf16::isSurrogatePair(const int32_t &charCode_) {
  return isSurrogatePair(charCode_, false);
};
bool Utf16::isSurrogatePair(const int32_t &charCode_, const bool &isSrcLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessSurrogatePairUint(charCode);
  }
  uint32_t highSurrogate;
  uint32_t lowSurrogate;
  // U+010000　〜　U+10FFFF
  highSurrogate = charCode & MaskHighSurrogatePair;
  lowSurrogate = charCode & MaskLowSurrogatePair;
  return HighSurrogatePairMin <= highSurrogate &&
         highSurrogate <= HighSurrogatePairMax &&
         LowSurrogatePairMin <= lowSurrogate &&
         lowSurrogate <= LowSurrogatePairMax;
};
bool Utf16::isValidCharCode(const int16_t &charCode_) {
  return isValidCharCode(int16_t(uint16_t(charCode_)), false, true);
};
bool Utf16::isValidCharCode(const int16_t &charCode_, const bool &isSrcLe_) {
  return isValidCharCode(int16_t(int16_t(charCode_)), isSrcLe_, true);
};
bool Utf16::isValidCharCode(const int16_t &charCode_, const bool &isSrcLe_,
                            const bool &isForString_) {
  if (isForString_) {
    return !(CharCode::Utf16::isLowSurrogate(int16_t(charCode_), isSrcLe_) ||
             CharCode::Utf16::isLineBreak(int16_t(charCode_), !isSrcLe_));
  } else {
    return !(CharCode::Utf16::isHighSurrogate(int16_t(charCode_), isSrcLe_) ||
             CharCode::Utf16::isLowSurrogate(int16_t(charCode_), isSrcLe_) ||
             CharCode::Utf16::isLineBreak(int16_t(charCode_), !isSrcLe_));
  }
};
bool Utf16::isValidCharCode(const int32_t &charCode_) {
  return isValidCharCode(charCode_, false, true);
};
bool Utf16::isValidCharCode(const int32_t &charCode_, const bool &isSrcLe_) {
  return isValidCharCode(charCode_, isSrcLe_, true);
};
bool Utf16::isValidCharCode(const int32_t &charCode_, const bool &isSrcLe_,
                            const bool &isForString_) {
  uint32_t charCode = (uint32_t)charCode_;
  // U+000000　〜　U+00FFFF
  if ((charCode & MaskHighSurrogatePair) == 0) {
    return isValidCharCode(int16_t(charCode_), isSrcLe_, isForString_);
  }
  // U+010000　〜　U+10FFFF
  return isSurrogatePair(charCode_, isSrcLe_);
};
int16_t Utf16::getBom(const bool &isDstLe_) {
  return isDstLe_ ? swapEndianness(BomCharCode) : int16_t(BomCharCode);
};
int16_t Utf16::getReplacementChar(const bool &isDstLe_) {
  return isDstLe_ ? swapEndianness(ReplacementCharCode)
                  : int16_t(ReplacementCharCode);
};
int16_t Utf16::swapEndianness(const int16_t &charCode_) {
  return int16_t(swapEndiannessUint(uint16_t(charCode_)));
};
uint16_t Utf16::swapEndiannessUint(const uint16_t &charCode_) {
  return ((charCode_ & MaskHighByte) >> SwapShiftByte) |
         ((charCode_ & MaskLowByte) << SwapShiftByte);
};
int32_t Utf16::swapEndiannessSurrogatePair(const int32_t &charCode_) {
  return int32_t(swapEndiannessSurrogatePairUint(uint32_t(charCode_)));
};
uint32_t Utf16::swapEndiannessSurrogatePairUint(const uint32_t &charCode_) {
  return ((charCode_ & Mask1stByte) >> SwapShiftByte) |
         ((charCode_ & Mask2ndByte) << SwapShiftByte) |
         ((charCode_ & Mask3rdByte) >> SwapShiftByte) |
         ((charCode_ & Mask4thByte) << SwapShiftByte);
};
std::vector<char> Utf16::toU8(const int16_t &charCode_) {
  return toU8(charCode_, false);
};
std::vector<char> Utf16::toU8(const int16_t &charCode_, const bool &isSrcLe_) {
  int32_t charCodeUtf32 = toU32(charCode_, isSrcLe_, false);
  return Utf32::toU8(charCodeUtf32);
};
std::vector<char> Utf16::toU8(const int32_t &charCode_) {
  return toU8(charCode_, false);
};
std::vector<char> Utf16::toU8(const int32_t &charCode_, const bool &isSrcLe_) {
  int32_t charCodeUtf32 = toU32(charCode_, isSrcLe_, false);
  return Utf32::toU8(charCodeUtf32);
};
int32_t Utf16::toU32(const int16_t &charCode_) {
  return toU32(charCode_, false, false);
};
int32_t Utf16::toU32(const int16_t &charCode_, const bool &isSrcLe_) {
  return toU32(charCode_, isSrcLe_, isSrcLe_);
};
int32_t Utf16::toU32(const int16_t &charCode_, const bool &isSrcLe_,
                     const bool &isDstLe_) {
  bool isSwapEndianness = isSrcLe_ != isDstLe_;
  // 3byte char : U+000800 〜 U+00FFFF
  // 2byte char : U+000080 〜 U+0007FF
  // 1byte char : U+000080 〜 U+00007F
  uint32_t charCode = (uint32_t)charCode_;
  if (isHighSurrogate(charCode_, isSrcLe_) ||
      isLowSurrogate(charCode_, isSrcLe_)) {
    return Utf32::getReplacementChar(isDstLe_);
  }
  if (isSwapEndianness) {
    charCode = (uint32_t)swapEndianness(charCode_);
  }
  if (isDstLe_) {
    charCode = charCode << ShiftLittleEndianness2Byte;
  } else {
    charCode = (charCode & MaskLow2Byte);
  }
  return (int32_t)charCode;
};
int32_t Utf16::toU32(const int32_t &charCode_) {
  return toU32(charCode_, false, false);
};
int32_t Utf16::toU32(const int32_t &charCode_, const bool &isSrcLe_) {
  return toU32(charCode_, isSrcLe_, isSrcLe_);
};
int32_t Utf16::toU32(const int32_t &charCode_, const bool &isSrcLe_,
                     const bool &isDstLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  // 3byte char : U+000800 〜 U+00FFFF
  // 2byte char : U+000080 〜 U+0007FF
  // 1byte char : U+000080 〜 U+00007F
  if ((charCode & MaskHigh2Byte) == 0) {
    return toU32(((int16_t)charCode_), isSrcLe_, isDstLe_);
  }
  // 4byte char : U+010000 〜 U+10FFFF
  if (!isSurrogatePair(charCode_, isSrcLe_)) {
    return Utf32::getReplacementChar(isDstLe_);
  }
  if (isSrcLe_) {
    charCode = swapEndiannessSurrogatePair(charCode_);
  }
  uint32_t charCodeUtf32 =
      U32NonBmpCodeMin +
      ((charCode >> U32ShiftHighSurrogate2Byte) - HighSurrogateCodeMin) *
          U32ShiftHighSurrogate2Factor +
      (charCode & MaskLow2Byte) - LowSurrogateCodeMin;
  if (isDstLe_) {
    return Utf32::swapEndianness((int32_t)charCodeUtf32);
  } else {
    return (int32_t)charCodeUtf32;
  }
};
std::string Utf16::toU8String(const int16_t &charCode_) {
  return toU8String(charCode_, false);
};
std::string Utf16::toU8String(const int16_t &charCode_, const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_)) {
    return std::string();
  }
  std::vector<char> chunk = toU8(charCode_, isSrcLe_);
  return std::string(chunk.begin(), chunk.end());
};
std::string Utf16::toU8String(const int32_t &charCode_) {
  return toU8String(charCode_, false);
};
std::string Utf16::toU8String(const int32_t &charCode_, const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_) || Utf32::isBom(charCode_, isSrcLe_)) {
    return std::string();
  }
  std::vector<char> chunk = toU8(charCode_, isSrcLe_);
  return std::string(chunk.begin(), chunk.end());
};
std::u16string Utf16::toU16String(const int16_t &charCode_) {
  return toU16String(charCode_, false);
};
std::u16string Utf16::toU16String(const int16_t &charCode_,
                                  const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_)) {
    return std::u16string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u16string();
  }
  return Utf32::toU16String(toU32(charCode_, isSrcLe_, false));
};
std::u16string Utf16::toU16String(const int32_t &charCode_) {
  return toU16String(charCode_, false);
};
std::u16string Utf16::toU16String(const int32_t &charCode_,
                                  const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_) || Utf32::isBom(charCode_, isSrcLe_)) {
    return std::u16string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u16string();
  }
  return Utf32::toU16String(toU32(charCode_, isSrcLe_, false));
};
std::u32string Utf16::toU32String(const int16_t &charCode_) {
  return toU32String(charCode_, false);
};
std::u32string Utf16::toU32String(const int16_t &charCode_,
                                  const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_)) {
    return std::u32string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u32string();
  }
  return Utf32::toU32String(toU32(charCode_, isSrcLe_, false));
};
std::u32string Utf16::toU32String(const int32_t &charCode_) {
  return toU32String(charCode_, false);
};
std::u32string Utf16::toU32String(const int32_t &charCode_,
                                  const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_) || Utf32::isBom(charCode_, isSrcLe_)) {
    return std::u32string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u32string();
  }
  return Utf32::toU32String(toU32(charCode_, isSrcLe_, false));
};
