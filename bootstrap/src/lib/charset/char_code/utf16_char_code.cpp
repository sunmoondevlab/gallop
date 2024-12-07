#include "charset/char_code/utf16_char_code.hpp"
#include "charset/char_code/utf32_char_code.hpp"

using namespace gallop::CharSet::CharCode;

bool Utf16::isNullCharCode(const int16_t &charCode_) { return charCode_ == 0; };
bool Utf16::isBom(const int16_t &charCode_) { return isBom(charCode_, false); };
bool Utf16::isBom(const int16_t &charCode_, const bool &isLE_) {
  // bom
  if (isLE_) {
    return ((uint16_t)(charCode_)) == static_cast<uint16_t>(0xfffe);
  } else {
    return ((uint16_t)(charCode_)) == static_cast<uint16_t>(0xfeff);
  }
};
bool Utf16::isHighSurrogate(const int16_t &charCode_) {
  return isHighSurrogate(charCode_, false);
};
bool Utf16::isHighSurrogate(const int16_t &charCode_, const bool &isLE_) {
  uint16_t surrogate;
  // U+D800　〜　U+DBFF
  if (isLE_) {
    surrogate = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0x00ff);
    return static_cast<uint16_t>(0x00d8) <= surrogate &&
           surrogate <= static_cast<uint16_t>(0x00db);
  } else {
    surrogate = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0xff00);
    return static_cast<uint16_t>(0xd800) <= surrogate &&
           surrogate <= static_cast<uint16_t>(0xdb00);
  }
};
bool Utf16::isLowSurrogate(const int16_t &charCode_) {
  return isLowSurrogate(charCode_, false);
};
bool Utf16::isLowSurrogate(const int16_t &charCode_, const bool &isLE_) {
  uint16_t surrogate;
  // U+DC00　〜　U+DFFF
  if (isLE_) {
    surrogate = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0x00ff);
    return static_cast<uint16_t>(0x00dc) <= surrogate &&
           surrogate <= static_cast<uint16_t>(0x00df);
  } else {
    surrogate = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0xff00);
    return static_cast<uint16_t>(0xdc00) <= surrogate &&
           surrogate <= static_cast<uint16_t>(0xdf00);
  }
};
bool Utf16::isNewLine(const int16_t &charCode_) {
  return isNewLine(charCode_, false);
};
bool Utf16::isNewLine(const int16_t &charCode_, const bool &isLE_) {
  // U+000A　,　U+000D
  if (isLE_) {
    return static_cast<uint16_t>(0x0a00) == ((uint16_t)(charCode_)) ||
           ((uint16_t)(charCode_)) == static_cast<uint16_t>(0x0d00);
  } else {
    return static_cast<uint16_t>(0x000a) == ((uint16_t)(charCode_)) ||
           ((uint16_t)(charCode_)) == static_cast<uint16_t>(0x000d);
  }
};
bool Utf16::isAscii(const int16_t &charCode_) {
  return isAscii(charCode_, false);
};
bool Utf16::isAscii(const int16_t &charCode_, const bool &isLE_) {
  uint16_t ascii;
  uint16_t nullByte;
  // U+0000　〜　U+007F
  if (isLE_) {
    ascii = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0xff00);
    nullByte = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0x00ff);
    return static_cast<uint16_t>(0x0000) <= ascii &&
           ascii <= static_cast<uint16_t>(0x7f00) &&
           nullByte == static_cast<uint16_t>(0x0000);
  } else {
    ascii = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0x00ff);
    nullByte = ((uint16_t)(charCode_)) & static_cast<uint16_t>(0xff00);
    return static_cast<uint16_t>(0x0000) <= ascii &&
           ascii <= static_cast<uint16_t>(0x007f) &&
           nullByte == static_cast<uint16_t>(0x0000);
  }
};
bool Utf16::isSurrogatePair(const int32_t &charCode_) {
  return isSurrogatePair(charCode_, false);
};
bool Utf16::isSurrogatePair(const int32_t &charCode_, const bool &isLE_) {
  uint32_t highSurrogate;
  uint32_t lowSurrogate;
  // U+010000　〜　U+10FFFF
  if (isLE_) {
    highSurrogate = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0x00ff0000);
    lowSurrogate = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0x000000ff);
    return static_cast<uint32_t>(0x00d80000) <= highSurrogate &&
           highSurrogate <= static_cast<uint32_t>(0x00db0000) &&
           static_cast<uint32_t>(0x000000dc) <= lowSurrogate &&
           lowSurrogate <= static_cast<uint32_t>(0x000000df);
  } else {
    highSurrogate = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0xff000000);
    lowSurrogate = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0x0000ff00);
    return static_cast<uint32_t>(0xd8000000) <= highSurrogate &&
           highSurrogate <= static_cast<uint32_t>(0xdb000000) &&
           static_cast<uint32_t>(0x0000dc00) <= lowSurrogate &&
           lowSurrogate <= static_cast<uint32_t>(0x0000df00);
  }
};

int16_t Utf16::swapEndianness(const int16_t &charCode_) {
  uint16_t charCode = (uint16_t)(charCode_);
  uint16_t toCharCode = ((charCode & static_cast<uint16_t>(0xff00)) >> 8) |
                        ((charCode & static_cast<uint16_t>(0x00ff)) << 8);
  return (int16_t)toCharCode;
};

int32_t Utf16::swapEndiannessSurrogatePair(const int32_t &charCode_) {
  uint32_t charCode = (uint32_t)(charCode_);
  uint32_t toCharCode = ((charCode & static_cast<uint32_t>(0xff000000)) >> 8) |
                        ((charCode & static_cast<uint32_t>(0x00ff0000)) << 8) |
                        ((charCode & static_cast<uint32_t>(0x0000ff00)) >> 8) |
                        ((charCode & static_cast<uint32_t>(0x000000ff)) << 8);
  return (uint32_t)toCharCode;
};
int32_t Utf16::toUtf32(const int16_t &charCode_) {
  return toUtf32(charCode_, false);
};
int32_t Utf16::toUtf32(const int16_t &charCode_, const bool &isLE_) {
  return toUtf32(charCode_, isLE_, false);
};
int32_t Utf16::toUtf32(const int16_t &charCode_, const bool &isLE_,
                       const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  // 3byte char : U+000800 〜 U+00FFFF
  // 2byte char : U+000080 〜 U+0007FF
  // 1byte char : U+000080 〜 U+00007F
  uint32_t charCode = (uint32_t)(charCode_);
  if (isHighSurrogate(charCode_, isLE_) || isLowSurrogate(charCode_, isLE_)) {
    if (isDstLE) {
      return static_cast<int32_t>(0xfdff0000);
    } else {
      return static_cast<int32_t>(0x0000fffd);
    }
  }
  if (isSwapEndianness_) {
    charCode = swapEndianness(charCode_);
  }
  if (isDstLE) {
    charCode = charCode << 16;
  } else {
    charCode = (charCode & static_cast<uint32_t>(0x0000ffff));
  }
  return (int32_t)charCode;
};
int32_t Utf16::toUtf32(const int32_t &charCode_) {
  return toUtf32(charCode_, false);
};
int32_t Utf16::toUtf32(const int32_t &charCode_, const bool &isLE_) {
  return toUtf32(charCode_, isLE_, false);
};
int32_t Utf16::toUtf32(const int32_t &charCode_, const bool &isLE_,
                       const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  uint32_t charCode = charCode_;
  // 3byte char : U+000800 〜 U+00FFFF
  // 2byte char : U+000080 〜 U+0007FF
  // 1byte char : U+000080 〜 U+00007F
  if ((charCode & static_cast<uint32_t>(0xffff0000)) == 0) {
    return toUtf32((int16_t)(charCode_), isLE_, isSwapEndianness_);
  }
  // 4byte char : U+010000 〜 U+10FFFF
  if (!isSurrogatePair(charCode_, isLE_)) {
    if (isDstLE) {
      return static_cast<int32_t>(0xfdff0000);
    } else {
      return static_cast<int32_t>(0x0000fffd);
    }
  }
  if (isLE_) {
    charCode = swapEndiannessSurrogatePair(charCode_);
  }
  uint32_t charCodeUtf32 =
      static_cast<uint32_t>(0x00010000) +
      (((uint32_t)charCode >> 16) - static_cast<uint32_t>(0xd800)) *
          static_cast<uint32_t>(0x400) +
      (((uint32_t)charCode) & static_cast<uint32_t>(0x0000ffff)) -
      static_cast<uint16_t>(0xdc00);
  if (isDstLE) {
    return Utf32::swapEndianness(((int32_t)charCodeUtf32));
  } else {
    return (int32_t)charCodeUtf32;
  }
};
std::vector<char> Utf16::toUtf8Chunk(const int16_t &charCode_) {
  return toUtf8Chunk(charCode_, false);
};
std::vector<char> Utf16::toUtf8Chunk(const int16_t &charCode_,
                                     const bool &isLE_) {
  int32_t charCodeUtf32 = toUtf32(charCode_, isLE_, isLE_);
  return Utf32::toUtf8Chunk(charCodeUtf32);
};
std::vector<char> Utf16::toUtf8Chunk(const int32_t &charCode_) {
  return toUtf8Chunk(charCode_, false);
};
std::vector<char> Utf16::toUtf8Chunk(const int32_t &charCode_,
                                     const bool &isLE_) {
  int32_t charCodeUtf32 = toUtf32(charCode_, isLE_, isLE_);
  return Utf32::toUtf8Chunk(charCodeUtf32);
};
std::string Utf16::toString(const int16_t &charCode_) {
  return toString(charCode_, false);
};
std::string Utf16::toString(const int16_t &charCode_, const bool &isLE_) {
  if (isBom(charCode_, isLE_)) {
    return "";
  }
  std::vector<char> chunk = toUtf8Chunk(charCode_, isLE_);
  return std::string(chunk.begin(), chunk.end());
};
std::string Utf16::toString(const int32_t &charCode_) {
  return toString(charCode_, false);
};
std::string Utf16::toString(const int32_t &charCode_, const bool &isLE_) {
  if (isBom(charCode_, isLE_) || Utf32::isBom(charCode_, isLE_)) {
    return "";
  }
  std::vector<char> chunk = toUtf8Chunk(charCode_, isLE_);
  return std::string(chunk.begin(), chunk.end());
};
