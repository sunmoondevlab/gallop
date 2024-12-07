// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/char_code/utf8_char_code.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf_ascii_table.hpp"

using namespace gallop::CharSet::CharCode;

bool Utf8::isNullCharCode(const char &charCode_) { return charCode_ == 0; };
bool Utf8::isBom(const int32_t &charCode_) {
  // bom
  return (uint32_t)charCode_ == BomCode;
};
int32_t Utf8::utf8FetchLength(const char &charCode_) {
  uint8_t charCode = (uint8_t)charCode_;
  // 4byte char : U+010000 〜 U+10FFFF
  if (HighestChar4ByteMin <= charCode && charCode <= HighestChar4ByteMax) {
    return 4;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if (HighestChar3ByteMin <= charCode && charCode <= HighestChar3ByteMax) {
    return 3;
  }
  // 2byte char : U+000080 〜 U+0007FF
  if (HighestChar2ByteMin <= charCode && charCode <= HighestChar2ByteMax) {
    return 2;
  }
  // 1byte char : U+000080 〜 U+00007F
  if (isAscii(charCode)) {
    return 1;
  }
  return 0;
};
bool Utf8::isContinuationByte(const char &charCode_) {
  uint8_t charCode = (uint8_t)charCode_;
  return ContinuationByteMin <= charCode && charCode <= ContinuationByteMax;
};
bool Utf8::isLineBreak(const char &charCode_) {
  // U+000A　,　U+000D
  return isLineFeed(charCode_) || isCarriageReturn(charCode_);
};
bool Utf8::isLineFeed(const char &charCode_) {
  // U+000A
  return ((uint8_t)charCode_) == static_cast<uint8_t>(UtfAsciiTable::LineFeed);
};
bool Utf8::isCarriageReturn(const char &charCode_) {
  // U+000D
  return ((uint8_t)charCode_) ==
         static_cast<uint8_t>(UtfAsciiTable::CarriageReturn);
};
bool Utf8::isAscii(const char &charCode_) {
  // U+0000　〜　U+007F
  return AsciiByteMin <= charCode_ && charCode_ <= AsciiByteMax;
};
bool Utf8::isValidCharCode(const int32_t &charCode_) {
  uint32_t charCode = (uint32_t)charCode_;
  // 4byte char : U+010000 〜 U+10FFFF
  if ((charCode & WeaklyMask4byteCode) > 0) {
    if ((charCode & StrictMask4byteCode) == ActualBit4byteCode &&
        (charCode & MaskContinuationByte3) == ActualBitContinuationByte3 &&
        (charCode & MaskContinuationByte2) == ActualBitContinuationByte2 &&
        (charCode & MaskContinuationByte1) == ActualBitContinuationByte1 &&
        CharCode4ByteMin <= charCode && charCode <= CharCode4ByteMax) {
      return true;
    }
    return false;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if ((charCode & WeaklyMask3byteCode) > 0) {
    if ((charCode & StrictMask3byteCode) == ActualBit3byteCode &&
        (charCode & MaskContinuationByte2) == ActualBitContinuationByte2 &&
        (charCode & MaskContinuationByte1) == ActualBitContinuationByte1 &&
        CharCode3ByteMin <= charCode &&
        (charCode < CharCode3SurrogateByteMin ||
         CharCode3SurrogateByteMax < charCode)) {
      return true;
    }
    return false;
  }
  // 2byte char : U+000080 〜 U+0007FF
  if ((charCode & WeaklyMask2byteCode) > 0) {
    if ((charCode & StrictMask2byteCode) == ActualBit2byteCode &&
        (charCode & MaskContinuationByte1) == ActualBitContinuationByte1 &&
        CharCode2ByteMin <= charCode) {
      return true;
    }
    return false;
  }
  // 1byte char : U+000080 〜 U+00007F
  if ((charCode & MaskNon1byteCode) == ActualBit1byteCode) {
    return true;
  }
  return false;
};
std::vector<char> Utf8::getBomChunk() {
  return std::vector<char>{char(BomCharCode0), char(BomCharCode1),
                           char(BomCharCode2)};
};
std::vector<char> Utf8::getReplacementCharChunk() {
  return std::vector<char>{char(ReplacementCharCode0),
                           char(ReplacementCharCode1),
                           char(ReplacementCharCode2)};
};
std::vector<char> Utf8::toU8(const int32_t &charCode_) {
  std::vector<char> chunk;
  if (isNullCharCode(charCode_)) {
    return chunk;
  }
  chunk.reserve(4);
  if (!isValidCharCode(charCode_)) {
    return getReplacementCharChunk();
  }
  uint32_t charCode = (uint32_t)charCode_;
  // 4byte char : U+010000 〜 U+10FFFF
  if ((charCode & WeaklyMask4byteCode) > 0) {
    chunk.push_back((char)(charCode >> ToU8ByteShift3));
    chunk.push_back((char)(charCode >> ToU8ByteShift2));
    chunk.push_back((char)(charCode >> ToU8ByteShift1));
    chunk.push_back((char)(charCode & ToU8CodePointMask1));
    return chunk;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if ((charCode & WeaklyMask3byteCode) > 0) {
    chunk.push_back((char)(charCode >> ToU8ByteShift2));
    chunk.push_back((char)(charCode >> ToU8ByteShift1));
    chunk.push_back((char)(charCode & ToU8CodePointMask1));
    return chunk;
  }
  // 2byte char : U+000080 〜 U+0007FF
  if ((charCode & WeaklyMask2byteCode) > 0) {
    chunk.push_back((char)(charCode >> ToU8ByteShift1));
    chunk.push_back((char)(charCode & ToU8CodePointMask1));
    return chunk;
  }
  // 1byte char : U+000080 〜 U+00007F
  chunk.push_back((char)(charCode & ToU8CodePointMask1));
  return chunk;
};
std::vector<int16_t> Utf8::toU16(const int32_t &charCode_) {
  return Utf32::toU16(toU32(charCode_), false, false);
};
std::vector<int16_t> Utf8::toU16(const int32_t &charCode_,
                                 const bool &isDstLe_) {
  return Utf32::toU16(toU32(charCode_), false, isDstLe_);
};

int32_t Utf8::toU32(const int32_t &charCode_) {
  return toU32(charCode_, false);
};
int32_t Utf8::toU32(const int32_t &charCode_, const bool &isDstLe_) {
  uint32_t charCode = (uint32_t)charCode_;
  if (!isValidCharCode(charCode_)) {
    return Utf32::getReplacementChar(isDstLe_);
  }
  uint32_t charCodeUtf32;
  // 4byte char : U+010000 〜 U+10FFFF
  if ((charCode & WeaklyMask4byteCode) > 0) {
    charCodeUtf32 =
        ((charCode & ToU32CodePointMaskHighest4) >> ToU32BitShift4) |
        ((charCode & ToU32CodePointMaskContinuation3) >> ToU32BitShift3) |
        ((charCode & ToU32CodePointMaskContinuation2) >> ToU32BitShift2) |
        (charCode & ToU32CodePointMaskContinuation1);
    if (isDstLe_) {
      return Utf32::swapEndianness((int32_t)charCodeUtf32);
    } else {
      return (int32_t)charCodeUtf32;
    }
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if ((charCode & WeaklyMask3byteCode) > 0) {
    charCodeUtf32 =
        ((charCode & ToU32CodePointMaskHighest3) >> ToU32BitShift3) |
        ((charCode & ToU32CodePointMaskContinuation2) >> ToU32BitShift2) |
        (charCode & ToU32CodePointMaskContinuation1);
    if (isDstLe_) {
      return Utf32::swapEndianness((int32_t)charCodeUtf32);
    } else {
      return (int32_t)charCodeUtf32;
    }
  }
  // 2byte char : U+000080 〜 U+0007FF
  if ((charCode & WeaklyMask2byteCode) > 0) {
    charCodeUtf32 =
        ((charCode & ToU32CodePointMaskHighest2) >> ToU32BitShift2) |
        (charCode & ToU32CodePointMaskContinuation1);
    if (isDstLe_) {
      return Utf32::swapEndianness((int32_t)charCodeUtf32);
    } else {
      return (int32_t)charCodeUtf32;
    }
  }
  // 1byte char : U+000080 〜 U+00007F
  charCodeUtf32 = charCode;
  if (isDstLe_) {
    return Utf32::swapEndianness(charCodeUtf32);
  } else {
    return (int32_t)charCodeUtf32;
  }
};
std::string Utf8::toU8String(const int32_t &charCode_) {
  if (isBom(charCode_)) {
    return std::string();
  }
  std::vector<char> chunk = toU8(charCode_);
  return std::string(chunk.begin(), chunk.end());
};
std::u16string Utf8::toU16String(const int32_t &charCode_) {
  if (isBom(charCode_)) {
    return std::u16string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u16string();
  }
  std::vector<int16_t> chunk = toU16(charCode_);
  return std::u16string(chunk.begin(), chunk.end());
};
std::u32string Utf8::toU32String(const int32_t &charCode_) {
  if (isBom(charCode_)) {
    return std::u32string();
  }
  if (isNullCharCode(charCode_)) {
    return std::u32string();
  }
  int32_t u32CharCode = toU32(charCode_);
  std::vector<int32_t> chunk = {u32CharCode};
  return std::u32string(chunk.begin(), chunk.end());
};
