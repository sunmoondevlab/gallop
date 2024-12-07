#include "charset/char_code/utf32_char_code.hpp"

using namespace gallop::CharSet::CharCode;

bool Utf32::isNullCharCode(const int32_t &charCode_) { return charCode_ == 0; };
bool Utf32::isBom(const int32_t &charCode_) { return isBom(charCode_, false); };
bool Utf32::isBom(const int32_t &charCode_, const bool &isLE_) {
  // bom
  if (isLE_) {
    return ((uint32_t)(charCode_)) == static_cast<uint32_t>(0xfffe0000);
  } else {
    return ((uint32_t)(charCode_)) == static_cast<uint32_t>(0x0000feff);
  }
};
bool Utf32::isNewLine(const int32_t &charCode_) {
  return isNewLine(charCode_, false);
};
bool Utf32::isNewLine(const int32_t &charCode_, const bool &isLE_) {
  // U+000A　,　U+000D
  if (isLE_) {
    return static_cast<uint32_t>(0x0a000000) == ((uint32_t)(charCode_)) ||
           ((uint32_t)(charCode_)) == static_cast<uint32_t>(0x0d000000);
  } else {
    return static_cast<uint32_t>(0x0000000a) == ((uint32_t)(charCode_)) ||
           ((uint32_t)(charCode_)) == static_cast<uint32_t>(0x0000000d);
  }
};
bool Utf32::isAscii(const int32_t &charCode_) {
  return isAscii(charCode_, false);
};
bool Utf32::isAscii(const int32_t &charCode_, const bool &isLE_) {
  uint32_t ascii;
  uint32_t nullByte;
  // U+0000　〜　U+007F
  if (isLE_) {
    ascii = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0xff000000);
    nullByte = ((uint32_t)(charCode_)) &
               static_cast<uint32_t>(0x00ffffff); // U+0000　〜　U+007F
    return static_cast<uint32_t>(0x00000000) <= ascii &&
           ascii <= static_cast<uint32_t>(0x7f000000) &&
           nullByte == static_cast<uint32_t>(0x00000000);
  } else {
    ascii = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0x000000ff);
    nullByte = ((uint32_t)(charCode_)) & static_cast<uint32_t>(0xffffff00);
    return static_cast<uint32_t>(0x00000000) <= ascii &&
           ascii <= static_cast<uint32_t>(0x0000007f) &&
           nullByte == static_cast<uint32_t>(0x00000000);
  }
};
bool Utf32::isValidCharCode(const int32_t &charCode_) {
  return isValidCharCode(charCode_, false);
};
bool Utf32::isValidCharCode(const int32_t &charCode_, const bool &isLE_) {
  // bom
  if (isBom(charCode_, isLE_)) {
    return true;
  }
  // U+0000 〜 U+10FFFF
  uint32_t charCode = (uint32_t)(charCode_);
  if (isLE_) {
    return (((charCode & static_cast<uint32_t>(0x000000ff)) ==
             static_cast<uint32_t>(0x00000000)) &&
            ((charCode & static_cast<uint32_t>(0x0000ff00)) <=
             static_cast<uint32_t>(0x00001000)) &&
            // not surrogate pare
            !((static_cast<uint32_t>(0x00d80000) <=
               (charCode & static_cast<uint32_t>(0x00ff0000))) &&
              ((charCode & static_cast<uint32_t>(0x00ff0000)) <=
               static_cast<uint32_t>(0x00df0000))));
  } else {
    return (((charCode & static_cast<uint32_t>(0xff000000)) ==
             static_cast<uint32_t>(0x00000000)) &&
            ((charCode & static_cast<uint32_t>(0x00ff0000)) <=
             static_cast<uint32_t>(0x00100000)) &&
            // not surrogate pare
            !((static_cast<uint32_t>(0x0000d800) <=
               (charCode & static_cast<uint32_t>(0x0000ff00))) &&
              ((charCode & static_cast<uint32_t>(0x0000ff00)) <=
               static_cast<uint32_t>(0x0000df00))));
  }
};
int32_t Utf32::swapEndianness(const int32_t &charCode_) {
  uint32_t charCode = (uint32_t)(charCode_);
  charCode = ((charCode & static_cast<uint32_t>(0xff000000)) >> 24) |
             ((charCode & static_cast<uint32_t>(0x00ff0000)) >> 8) |
             ((charCode & static_cast<uint32_t>(0x0000ff00)) << 8) |
             ((charCode & static_cast<uint32_t>(0x000000ff)) << 24);
  return (int32_t)charCode;
};
std::vector<char> Utf32::toUtf8Chunk(const int32_t &charCode_) {
  return toUtf8Chunk(charCode_, false);
};
std::vector<char> Utf32::toUtf8Chunk(const int32_t &charCode_,
                                     const bool &isLE_) {
  std::vector<char> chunk;
  if (isNullCharCode(charCode_)) {
    return chunk;
  }
  uint32_t charCode = charCode_;
  if (isLE_) {
    charCode = (uint32_t)swapEndianness(charCode);
  }
  chunk.reserve(4);
  if (isBom((int32_t)charCode)) {
    chunk.push_back(static_cast<char>(0xef));
    chunk.push_back(static_cast<char>(0xbb));
    chunk.push_back(static_cast<char>(0xbf));
    return chunk;
  }
  if (!isValidCharCode((int32_t)charCode)) {
    chunk.push_back(static_cast<char>(0xef));
    chunk.push_back(static_cast<char>(0xbf));
    chunk.push_back(static_cast<char>(0xbd));
    return chunk;
  }
  // 4byte char : U+010000 〜 U+10FFFF
  if (charCode >= static_cast<uint32_t>(0x00010000)) {
    chunk.push_back((char)(static_cast<char>(0xf0) | (charCode >> 18)));
    chunk.push_back((char)(static_cast<char>(0x80) |
                           ((charCode >> 12) & static_cast<char>(0x3f))));
    chunk.push_back((char)(static_cast<char>(0x80) |
                           ((charCode >> 6) & static_cast<char>(0x3f))));
    chunk.push_back(
        (char)(static_cast<char>(0x80) | (charCode & static_cast<char>(0x3f))));
    return chunk;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  else if (charCode >= static_cast<uint32_t>(0x00000800)) {
    chunk.push_back((char)(static_cast<char>(0xe0) | (charCode >> 12)));
    chunk.push_back((char)(static_cast<char>(0x80) |
                           ((charCode >> 6) & static_cast<char>(0x3f))));
    chunk.push_back(
        (char)(static_cast<char>(0x80) | (charCode & static_cast<char>(0x3f))));
    return chunk;
  }
  // 2byte char : U+000080 〜 U+0007FF
  else if (charCode >= static_cast<uint32_t>(0x00000080)) {
    chunk.push_back((char)(static_cast<char>(0xc0) | (charCode >> 6)));
    chunk.push_back(
        (char)(static_cast<char>(0x80) | (charCode & static_cast<char>(0x3f))));
    return chunk;
  }
  // 1byte char : U+000080 〜 U+00007F
  else {
    chunk.push_back((char)(charCode));
    return chunk;
  }
};
std::string Utf32::toString(const int32_t &charCode_) {
  return toString(charCode_, false);
};
std::string Utf32::toString(const int32_t &charCode_, const bool &isLE_) {
  if (isBom(charCode_, isLE_)) {
    return "";
  }
  std::vector<char> chunk = toUtf8Chunk(charCode_, isLE_);
  return std::string(chunk.begin(), chunk.end());
};
std::vector<int16_t> Utf32::toUtf16Chunk(const int32_t &charCode_) {
  return toUtf16Chunk(charCode_, false);
};
std::vector<int16_t> Utf32::toUtf16Chunk(const int32_t &charCode_,
                                         const bool &isLE_) {
  return toUtf16Chunk(charCode_, isLE_, false);
};
std::vector<int16_t> Utf32::toUtf16Chunk(const int32_t &charCode_,
                                         const bool &isLE_,
                                         const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  uint32_t charCode = charCode_;
  std::vector<int16_t> chunk;
  chunk.reserve(2);
  if (!isValidCharCode((int32_t)charCode, isLE_)) {
    if (isDstLE) {
      chunk.push_back(static_cast<int16_t>(0xfdff));
    } else {
      chunk.push_back(static_cast<int16_t>(0xfffd));
    }
    return chunk;
  }
  if (isLE_) {
    charCode = swapEndianness(charCode);
  }
  // 4byte char : U+010000 〜 U+10FFFF
  if (charCode >= static_cast<uint32_t>(0x00010000)) {
    uint32_t surrogateCharCode = charCode - static_cast<uint32_t>(0x00010000);
    uint16_t charCode16High =
        uint16_t(surrogateCharCode / static_cast<uint16_t>(0x400) +
                 static_cast<uint16_t>(0xd800));
    uint16_t charCode16Low =
        uint16_t(surrogateCharCode % static_cast<uint16_t>(0x400) +
                 static_cast<uint16_t>(0xdc00));
    if (isDstLE) {
      chunk.push_back(
          (int16_t)(((charCode16High & static_cast<uint16_t>(0xff00)) >> 8) |
                    ((charCode16High & static_cast<uint16_t>(0x00ff)) << 8)));
      chunk.push_back(
          (int16_t)(((charCode16Low & static_cast<uint16_t>(0xff00)) >> 8) |
                    ((charCode16Low & static_cast<uint16_t>(0x00ff)) << 8)));
    } else {
      chunk.push_back((int16_t)(charCode16High));
      chunk.push_back((int16_t)(charCode16Low));
    }
    return chunk;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  // 2byte char : U+000080 〜 U+0007FF
  // 1byte char : U+000080 〜 U+00007F
  else {
    if (isDstLE) {
      chunk.push_back(
          (int16_t)(((charCode & static_cast<uint16_t>(0xff00)) >> 8) |
                    ((charCode & static_cast<uint16_t>(0x00ff)) << 8)));
      return chunk;
    } else {
      chunk.push_back(((int16_t)charCode));
      return chunk;
    }
  }
};
