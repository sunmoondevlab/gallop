// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/char_code/utf32_char_code.hpp"

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"
#include "error/common_errors.hpp"

using namespace gallop::Error;
using namespace gallop::CharSet::CharCode;

bool Utf32::isNullCharCode(const int32_t &charCode_) { return charCode_ == 0; };
bool Utf32::isBom(const int32_t &charCode_) { return isBom(charCode_, false); };
bool Utf32::isBom(const int32_t &charCode_, const bool &isSrcLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // bom
  return charCode == BomCharCode;
};
bool Utf32::isLineBreak(const int32_t &charCode_) {
  return isLineBreak(charCode_, false);
};
bool Utf32::isLineBreak(const int32_t &charCode_, const bool &isSrcLe_) {
  // U+000A　,　U+000D
  return isLineFeed(charCode_, isSrcLe_) ||
         isCarriageReturn(charCode_, isSrcLe_);
};
bool Utf32::isLineFeed(const int32_t &charCode_) {
  return isLineFeed(charCode_, false);
};
bool Utf32::isLineFeed(const int32_t &charCode_, const bool &isSrcLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // U+000A
  return charCode == static_cast<uint32_t>(UtfAsciiTable::LineFeed);
};
bool Utf32::isCarriageReturn(const int32_t &charCode_) {
  return isCarriageReturn(charCode_, false);
};
bool Utf32::isCarriageReturn(const int32_t &charCode_, const bool &isSrcLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // U+000D
  return charCode == static_cast<uint32_t>(UtfAsciiTable::CarriageReturn);
};
bool Utf32::isAscii(const int32_t &charCode_) {
  return isAscii(charCode_, false);
};
bool Utf32::isAscii(const int32_t &charCode_, const bool &isSrcLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  return AsciiByteMin <= charCode && charCode <= AsciiByteMax;
};
bool Utf32::isValidCharCode(const int32_t &charCode_) {
  return isValidCharCode(charCode_, false);
};
bool Utf32::isValidCharCode(const int32_t &charCode_, const bool &isSrcLe_) {
  // bom
  if (isBom(charCode_, isSrcLe_)) {
    return true;
  }
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  // U+0000 〜 U+10FFFF
  return ((CodePointMin <= charCode && charCode <= CodePointMax) &&
          // not surrogate pare
          !(SurrogateCodeMin <= charCode && charCode <= SurrogateCodeMax));
};
int32_t Utf32::getBom(const bool &isDstLe_) {
  return isDstLe_ ? swapEndiannessUint(BomCharCode) : int32_t(BomCharCode);
};
int32_t Utf32::getReplacementChar(const bool &isDstLe_) {
  return isDstLe_ ? swapEndiannessUint(ReplacementCharCode)
                  : int32_t(ReplacementCharCode);
};
int32_t Utf32::swapEndianness(const int32_t &charCode_) {
  return int32_t(swapEndiannessUint(uint32_t(charCode_)));
};
uint32_t Utf32::swapEndiannessUint(const uint32_t &charCode_) {
  return ((charCode_ & Mask1stByte) >> SwapShiftOuterByte) |
         ((charCode_ & Mask2ndByte) >> SwapShiftInnerByte) |
         ((charCode_ & Mask3rdByte) << SwapShiftInnerByte) |
         ((charCode_ & Mask4thByte) << SwapShiftOuterByte);
};
std::vector<char> Utf32::toU8(const int32_t &charCode_) {
  return toU8(charCode_, false);
};
std::vector<char> Utf32::toU8(const int32_t &charCode_, const bool &isSrcLe_) {
  std::vector<char> chunk;
  if (isNullCharCode(charCode_)) {
    return chunk;
  }
  uint32_t charCode = (uint32_t)charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  chunk.reserve(4);
  if (isBom(charCode)) {
    return Utf8::getBomChunk();
  }
  if (!isValidCharCode(charCode)) {
    return Utf8::getReplacementCharChunk();
  }
  // 4byte char : U+010000 〜 U+10FFFF
  if (charCode >= CodePoint4ByteU8Min) {
    chunk.push_back((char)(FlagHighestChar4Byte | (charCode >> Shift1stByte)));
    chunk.push_back((char)(FlagContinuation2Byte | ((charCode >> Shift2ndByte) &
                                                    MaskContinuationByte)));
    chunk.push_back((char)(FlagContinuation2Byte | ((charCode >> Shift3rdByte) &
                                                    MaskContinuationByte)));
    chunk.push_back(
        (char)(FlagContinuation2Byte | (charCode & MaskContinuationByte)));
    return chunk;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  else if (charCode >= CodePoint3ByteU8Min) {
    chunk.push_back((char)(FlagHighestChar3Byte | (charCode >> Shift2ndByte)));
    chunk.push_back((char)(FlagContinuation2Byte | ((charCode >> Shift3rdByte) &
                                                    MaskContinuationByte)));
    chunk.push_back(
        (char)(FlagContinuation2Byte | (charCode & MaskContinuationByte)));
    return chunk;
  }
  // 2byte char : U+000080 〜 U+0007FF
  else if (charCode >= CodePoint2ByteU8Min) {
    chunk.push_back((char)(FlagHighestChar2Byte | (charCode >> Shift3rdByte)));
    chunk.push_back(
        (char)(FlagContinuation2Byte | (charCode & MaskContinuationByte)));
    return chunk;
  }
  // 1byte char : U+000080 〜 U+00007F
  else {
    chunk.push_back((char)(charCode));
    return chunk;
  }
};
std::vector<int16_t> Utf32::toU16(const int32_t &charCode_) {
  return toU16(charCode_, false, false);
};
std::vector<int16_t> Utf32::toU16(const int32_t &charCode_,
                                  const bool &isSrcLe_) {
  return toU16(charCode_, isSrcLe_, isSrcLe_);
};
std::vector<int16_t> Utf32::toU16(const int32_t &charCode_,
                                  const bool &isSrcLe_, const bool &isDstLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  std::vector<int16_t> chunk;
  chunk.reserve(2);
  if (!isValidCharCode(charCode_, isSrcLe_)) {
    chunk.push_back(Utf16::getReplacementChar(isDstLe_));
    return chunk;
  }
  if (isSrcLe_) {
    charCode = (uint32_t)swapEndiannessUint(charCode_);
  }
  // 4byte char : U+010000 〜 U+10FFFF
  if (charCode >= CodePoint4ByteU8Min) {
    uint32_t surrogateCharCode = charCode - CodePoint4ByteU8Min;
    uint16_t charCode16High =
        (uint16_t)(surrogateCharCode / U32DivideHighSurrogate2Factor +
                   U16HighSurrogateCodeMin);
    uint16_t charCode16Low =
        (uint16_t)(surrogateCharCode % U32DivideHighSurrogate2Factor +
                   U16LowSurrogateCodeMin);
    if (isDstLe_) {
      chunk.push_back(Utf16::swapEndianness(charCode16High));
      chunk.push_back(Utf16::swapEndianness(charCode16Low));
    } else {
      chunk.push_back((int16_t)charCode16High);
      chunk.push_back((int16_t)charCode16Low);
    }
    return chunk;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  // 2byte char : U+000080 〜 U+0007FF
  // 1byte char : U+000080 〜 U+00007F
  else {
    if (isDstLe_) {
      chunk.push_back(Utf16::swapEndianness(charCode));
      return chunk;
    } else {
      chunk.push_back((int16_t)charCode);
      return chunk;
    }
  }
};
std::string Utf32::toU8String(const int32_t &charCode_) {
  return toU8String(charCode_, false);
};
std::string Utf32::toU8String(const int32_t &charCode_, const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_)) {
    return std::string();
  }
  std::vector<char> chunk = toU8(charCode_, isSrcLe_);
  return std::string(chunk.begin(), chunk.end());
};
std::u16string Utf32::toU16String(const int32_t &charCode_) {
  return toU16String(charCode_, false);
};
std::u16string Utf32::toU16String(const int32_t &charCode_,
                                  const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_)) {
    return std::u16string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u16string();
  }
  std::vector<int16_t> chunk = toU16(charCode_, isSrcLe_, false);
  return std::u16string(chunk.begin(), chunk.end());
};
std::u32string Utf32::toU32String(const int32_t &charCode_) {
  return toU32String(charCode_, false);
};
std::u32string Utf32::toU32String(const int32_t &charCode_,
                                  const bool &isSrcLe_) {
  if (isBom(charCode_, isSrcLe_)) {
    return std::u32string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u32string();
  }
  int32_t charCode = charCode_;
  if (isSrcLe_) {
    charCode = swapEndiannessUint(charCode);
  }
  if (!isValidCharCode(charCode)) {
    charCode = Utf32::getReplacementChar(false);
  }
  std::vector<int32_t> chunk{charCode};
  return std::u32string(chunk.begin(), chunk.end());
};

bool Utf32::isSpaceChar(const int32_t &charCode_) {
  uint32_t charCode = uint32_t(charCode_);
  return charCode == static_cast<uint32_t>(UtfAsciiTable::HorizontalTab) ||
         charCode == static_cast<uint32_t>(UtfAsciiTable::VerticalTab) ||
         charCode == static_cast<uint32_t>(UtfAsciiTable::FormFeed) ||
         charCode == static_cast<uint32_t>(UtfAsciiTable::Space);
};
bool Utf32::isNumberChar(const int32_t &charCode_) {
  uint32_t charCode = uint32_t(charCode_);
  return static_cast<uint32_t>(UtfAsciiTable::Number0) <= charCode &&
         charCode <= static_cast<uint32_t>(UtfAsciiTable::Number9);
};
bool Utf32::isUpperAlphaChar(const int32_t &charCode_) {
  uint32_t charCode = uint32_t(charCode_);
  return static_cast<uint32_t>(UtfAsciiTable::UpperA) <= charCode &&
         charCode <= static_cast<uint32_t>(UtfAsciiTable::UpperZ);
};
bool Utf32::isLowerAlphaChar(const int32_t &charCode_) {
  uint32_t charCode = uint32_t(charCode_);
  return static_cast<uint32_t>(UtfAsciiTable::LowerA) <= charCode &&
         charCode <= static_cast<uint32_t>(UtfAsciiTable::LowerZ);
};
bool Utf32::isAlphabetChar(const int32_t &charCode_) {
  return isUpperAlphaChar(charCode_) || isLowerAlphaChar(charCode_);
};
bool Utf32::isAlphabetNumberChar(const int32_t &charCode_) {
  return isNumberChar(charCode_) || isAlphabetChar(charCode_);
};
bool Utf32::isSymbolChar(const int32_t &charCode_) {
  uint32_t charCode = uint32_t(charCode_);
  return (static_cast<uint32_t>(UtfAsciiTable::Exclamation) <= charCode &&
          charCode <= static_cast<uint32_t>(UtfAsciiTable::Slash)) ||
         (static_cast<uint32_t>(UtfAsciiTable::Colon) <= charCode &&
          charCode <= static_cast<uint32_t>(UtfAsciiTable::AtSign)) ||
         (static_cast<uint32_t>(UtfAsciiTable::SquareBracketOpen) <= charCode &&
          charCode <= static_cast<uint32_t>(UtfAsciiTable::BackQuotation)) ||
         (static_cast<uint32_t>(UtfAsciiTable::CurlyBracketOpen) <= charCode &&
          charCode <= static_cast<uint32_t>(UtfAsciiTable::Tilde));
};
bool Utf32::isIdentifierChar(const int32_t &charCode_) {
  return isIdentifierChar(charCode_, false);
};
bool Utf32::isIdentifierChar(const int32_t &charCode_,
                             const bool &isContinue_) {
  if (isContinue_) {
    uint32_t charCode = uint32_t(charCode_);
    return charCode == static_cast<uint32_t>(UtfAsciiTable::Underline) ||
           isAlphabetNumberChar(charCode_);
  } else {
    uint32_t charCode = uint32_t(charCode_);
    return charCode == static_cast<uint32_t>(UtfAsciiTable::Underline) ||
           isAlphabetChar(charCode_);
  }
}
bool Utf32::isBinaryDigitChar(const int32_t &charCode_) {
  return isDigitCharByRadix(charCode_, 2, false);
};
bool Utf32::isBinaryDigitChar(const int32_t &charCode_,
                              const bool &isForNumberLiteral_) {
  return isDigitCharByRadix(charCode_, 2, isForNumberLiteral_);
};
bool Utf32::isOctalDigitChar(const int32_t &charCode_) {
  return isDigitCharByRadix(charCode_, 8, false);
};
bool Utf32::isOctalDigitChar(const int32_t &charCode_,
                             const bool &isForNumberLiteral_) {
  return isDigitCharByRadix(charCode_, 8, isForNumberLiteral_);
};
bool Utf32::isDecimalDigitChar(const int32_t &charCode_) {
  return isDigitCharByRadix(charCode_, 10, false);
};
bool Utf32::isDecimalDigitChar(const int32_t &charCode_,
                               const bool &isForNumberLiteral_) {
  return isDigitCharByRadix(charCode_, 10, isForNumberLiteral_);
};
bool Utf32::isHexadecimalDigitChar(const int32_t &charCode_) {
  return isDigitCharByRadix(charCode_, 16, false);
};
bool Utf32::isHexadecimalDigitChar(const int32_t &charCode_,
                                   const bool &isForNumberLiteral_) {
  return isDigitCharByRadix(charCode_, 16, isForNumberLiteral_);
};
bool Utf32::isDigitCharByRadix(const int32_t &charCode_, const uint8_t radix_) {
  return isDigitCharByRadix(charCode_, radix_, false, false);
};
bool Utf32::isDigitCharByRadix(const int32_t &charCode_, const uint8_t radix_,
                               const bool &isForNumberLiteral_) {
  return isDigitCharByRadix(charCode_, radix_, false, isForNumberLiteral_);
};
bool Utf32::isDigitCharByRadix(const int32_t &charCode_, const uint8_t radix_,
                               const bool &isLowerPrefer_,
                               const bool &isForNumberLiteral_) {
  if (radix_ < MinRadix || MaxRadix < radix_) {
    throw new InvalidArgumentError(
        "invalid radix. radix is only between 2 and 62 are allowed. radix = " +
        std::to_string(radix_) + ".\n");
  }
  if (uint32_t(charCode_) == static_cast<uint32_t>(UtfAsciiTable::Underline)) {
    return isForNumberLiteral_;
  }
  uint32_t charCode = uint32_t(charCode_);
  uint32_t maxNumberDigitChar = static_cast<uint32_t>(UtfAsciiTable::Number9);
  if (radix_ <= NumOnlyMaxRadix) {
    maxNumberDigitChar =
        static_cast<int32_t>(UtfAsciiTable::Number0) + (radix_ - 1);
    return (static_cast<uint32_t>(UtfAsciiTable::Number0) <= charCode &&
            charCode <= maxNumberDigitChar);
  }
  uint32_t maxUpperDigitChar = static_cast<uint32_t>(UtfAsciiTable::UpperZ);
  uint32_t maxLowerDigitChar = static_cast<uint32_t>(UtfAsciiTable::LowerZ);
  if (radix_ <= CiAlphabetNumMaxRadix) {
    maxUpperDigitChar = static_cast<int32_t>(UtfAsciiTable::UpperA) +
                        (radix_ - CiAlphabetNumMinRadix);
    maxLowerDigitChar = static_cast<int32_t>(UtfAsciiTable::LowerA) +
                        (radix_ - CiAlphabetNumMinRadix);
  } else {
    if (isLowerPrefer_) {
      maxUpperDigitChar = static_cast<int32_t>(UtfAsciiTable::UpperA) +
                          (radix_ - CsAlphabetNumMinRadix);
    } else {
      maxLowerDigitChar = static_cast<int32_t>(UtfAsciiTable::LowerA) +
                          (radix_ - CsAlphabetNumMinRadix);
    }
  }
  return isNumberChar(charCode_) ||
         (static_cast<uint32_t>(UtfAsciiTable::UpperA) <= charCode &&
          charCode <= maxUpperDigitChar) ||
         (static_cast<uint32_t>(UtfAsciiTable::LowerA) <= charCode &&
          charCode <= maxLowerDigitChar);
};

bool Utf32::equalsCharIgnoreCase(const int32_t &charCode_,
                                 const int32_t &expectCharCode_) {
  uint32_t charCode = uint32_t(charCode_);
  uint32_t expectCharCode = uint32_t(expectCharCode_);
  if (isLowerAlphaChar(charCode_)) {
    charCode = charCode_ - (static_cast<uint32_t>(UtfAsciiTable::LowerA) -
                            static_cast<uint32_t>(UtfAsciiTable::UpperA));
  }
  if (isLowerAlphaChar(expectCharCode_)) {
    expectCharCode =
        expectCharCode_ - (static_cast<uint32_t>(UtfAsciiTable::LowerA) -
                           static_cast<uint32_t>(UtfAsciiTable::UpperA));
  }
  return charCode == expectCharCode;
};
int32_t Utf32::toDecimalFromBinaryChar(const int32_t &charCode_) {
  return toDecimalFromDigitCharByRadix(charCode_, 2);
};
int32_t Utf32::toDecimalFromOctalChar(const int32_t &charCode_) {
  return toDecimalFromDigitCharByRadix(charCode_, 8);
};
int32_t Utf32::toDecimalFromDecimalChar(const int32_t &charCode_) {
  return toDecimalFromDigitCharByRadix(charCode_, 10);
};
int32_t Utf32::toDecimalFromHexadecimalChar(const int32_t &charCode_) {
  return toDecimalFromDigitCharByRadix(charCode_, 16);
};
int32_t Utf32::toDecimalFromDigitCharByRadix(const int32_t &charCode_,
                                             const uint8_t radix_) {
  return toDecimalFromDigitCharByRadix(charCode_, radix_, false);
};
int32_t Utf32::toDecimalFromDigitCharByRadix(const int32_t &charCode_,
                                             const uint8_t radix_,
                                             const bool &isLowerPrefer_) {
  if (radix_ < MinRadix || MaxRadix < radix_) {
    throw new InvalidArgumentError(
        "invalid radix. radix is only between 2 and 62 are allowed. radix = " +
        std::to_string(radix_) + ".\n");
  }
  if (!isDigitCharByRadix(charCode_, radix_, isLowerPrefer_, false)) {
    if (radix_ > CiAlphabetNumMaxRadix && isLowerPrefer_) {
      throw new InvalidArgumentError(
          "invalid digit char in radix(lower prefer) = " +
          std::to_string(radix_) + ". digit char = " + toU8String(charCode_) +
          ".\n");
    }
    throw new InvalidArgumentError(
        "invalid digit char in radix = " + std::to_string(radix_) +
        ". digit char = " + toU8String(charCode_) + ".\n");
  }
  uint32_t charCode = uint32_t(charCode_);
  if (charCode <= static_cast<uint32_t>(UtfAsciiTable::Number9)) {
    return charCode - static_cast<uint32_t>(UtfAsciiTable::Number0);
  }
  if (charCode <= static_cast<uint32_t>(UtfAsciiTable::UpperZ)) {
    if (radix_ > CiAlphabetNumMaxRadix && isLowerPrefer_) {
      return charCode - static_cast<uint32_t>(UtfAsciiTable::UpperA) +
             CiAlphabetNumMaxRadix;
    } else {
      return charCode - static_cast<uint32_t>(UtfAsciiTable::UpperA) +
             NumOnlyMaxRadix;
    }
  }
  if (radix_ > CiAlphabetNumMaxRadix && !isLowerPrefer_) {
    return charCode - static_cast<uint32_t>(UtfAsciiTable::LowerA) +
           CiAlphabetNumMaxRadix;
  } else {
    return charCode - static_cast<uint32_t>(UtfAsciiTable::LowerA) +
           NumOnlyMaxRadix;
  }
};
int32_t Utf32::toBinaryCharFromDecimal(const int32_t &digit_) {
  return toDigitCharFromDecimalByRadix(digit_, 2, false);
};
int32_t Utf32::toOctalCharFromDecimal(const int32_t &digit_) {
  return toDigitCharFromDecimalByRadix(digit_, 8, false);
};
int32_t Utf32::toDecimalCharFromDecimal(const int32_t &digit_) {
  return toDigitCharFromDecimalByRadix(digit_, 10, false);
};
int32_t Utf32::toHexadecimalCharFromDecimal(const int32_t &digit_) {
  return toDigitCharFromDecimalByRadix(digit_, 16, true);
};
int32_t Utf32::toHexadecimalCharFromDecimal(const int32_t &digit_,
                                            const bool &isLowerPrefer_) {
  return toDigitCharFromDecimalByRadix(digit_, 16, isLowerPrefer_);
};
int32_t Utf32::toDigitCharFromDecimalByRadix(const int32_t &digit_,
                                             const uint8_t radix_) {
  return toDigitCharFromDecimalByRadix(digit_, radix_, false);
};
int32_t Utf32::toDigitCharFromDecimalByRadix(const int32_t &digit_,
                                             const uint8_t radix_,
                                             const bool &isLowerPrefer_) {
  if (radix_ < MinRadix || MaxRadix < radix_) {
    throw new InvalidArgumentError(
        "invalid radix. radix is only between 2 and 62 are allowed. radix = " +
        std::to_string(radix_) + ".\n");
  }
  if (digit_ >= radix_) {
    throw new InvalidArgumentError(
        "invalid digit in radix = " + std::to_string(radix_) +
        ". digit is only less than radix. digit = " + std::to_string(digit_) +
        ".\n");
  }
  if (digit_ < NumOnlyMaxRadix) {
    return (static_cast<uint32_t>(UtfAsciiTable::Number0) + digit_);
  }
  if (digit_ < CiAlphabetNumMaxRadix) {
    if (isLowerPrefer_) {
      return (static_cast<uint32_t>(UtfAsciiTable::LowerA) +
              (digit_ - NumOnlyMaxRadix));
    } else {
      return (static_cast<uint32_t>(UtfAsciiTable::UpperA) +
              (digit_ - NumOnlyMaxRadix));
    }
  }
  if (isLowerPrefer_) {
    return (static_cast<uint32_t>(UtfAsciiTable::UpperA) +
            (digit_ - CiAlphabetNumMaxRadix));
  } else {
    return (static_cast<uint32_t>(UtfAsciiTable::LowerA) +
            (digit_ - CiAlphabetNumMaxRadix));
  }
};
