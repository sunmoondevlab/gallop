#include "charset/char_code/utf8_char_code.hpp"
#include "charset/char_code/utf32_char_code.hpp"

using namespace gallop::CharSet::CharCode;

bool Utf8::isNullCharCode(const int8_t &charCode_) { return charCode_ == 0; };
bool Utf8::isBom(const int32_t &charCode_) {
  // bom
  return ((uint32_t)(charCode_)) == static_cast<uint32_t>(0xefbbbf);
};
int32_t Utf8::utf8FetchLength(const int8_t &charCode_) {
  uint8_t charCode = (uint8_t)charCode_;
  // 4byte char : U+010000 〜 U+10FFFF
  if (static_cast<uint8_t>(0xf0) <= charCode &&
      charCode <= static_cast<uint8_t>(0xf4)) {
    return 4;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if (static_cast<uint8_t>(0xe0) <= charCode &&
      charCode <= static_cast<uint8_t>(0xef)) {
    return 3;
  }
  // 2byte char : U+000080 〜 U+0007FF
  if (static_cast<uint8_t>(0xc2) <= charCode &&
      charCode <= static_cast<uint8_t>(0xdf)) {
    return 2;
  }
  // 1byte char : U+000080 〜 U+00007F
  if (static_cast<uint8_t>(0x00) <= charCode &&
      charCode <= static_cast<uint8_t>(0x7f)) {
    return 1;
  }
  return 0;
};
bool Utf8::isContinuationByte(const int8_t &charCode_) {
  uint8_t charCode = (uint8_t)charCode_;
  return static_cast<uint8_t>(0x80) <= charCode &&
         charCode <= static_cast<uint8_t>(0xbf);
};
bool Utf8::isNewLine(const int8_t &charCode_) {
  // U+000A　,　U+000D
  return static_cast<uint8_t>(0x000a) == ((uint8_t)(charCode_)) ||
         ((uint8_t)(charCode_)) == static_cast<uint8_t>(0x000d);
};
bool Utf8::isAscii(const int8_t &charCode_) {
  // U+0000　〜　U+007F
  return static_cast<uint8_t>(0x0000) <= ((uint8_t)(charCode_)) &&
         ((uint8_t)(charCode_)) <= static_cast<uint8_t>(0x007f);
};
bool Utf8::isValidCharCode(const int32_t &charCode_) {
  uint32_t charCode = (uint32_t)charCode_;
  // 4byte char : U+010000 〜 U+10FFFF
  if ((charCode & static_cast<uint32_t>(0xff000000)) > 0) {
    if ((charCode & static_cast<uint32_t>(0xf8000000)) ==
            static_cast<uint32_t>(0xf0000000) &&
        (charCode & static_cast<uint32_t>(0x00c00000)) ==
            static_cast<uint32_t>(0x00800000) &&
        (charCode & static_cast<uint32_t>(0x0000c000)) ==
            static_cast<uint32_t>(0x00008000) &&
        (charCode & static_cast<uint32_t>(0x000000c0)) ==
            static_cast<uint32_t>(0x00000080) &&
        static_cast<uint32_t>(0xf0908080) <= charCode &&
        charCode <= static_cast<uint32_t>(0xf48fbfbf)) {
      return true;
    }
    return false;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if ((charCode & static_cast<uint32_t>(0xffff0000)) > 0) {
    if ((charCode & static_cast<uint32_t>(0xfff00000)) ==
            static_cast<uint32_t>(0x00e00000) &&
        (charCode & static_cast<uint32_t>(0x0000c000)) ==
            static_cast<uint32_t>(0x00008000) &&
        (charCode & static_cast<uint32_t>(0x000000c0)) ==
            static_cast<uint32_t>(0x00000080) &&
        static_cast<uint32_t>(0x00e0a080) <= charCode &&
        (static_cast<uint32_t>(0x00eda080) > charCode ||
         charCode > static_cast<uint32_t>(0x00edbfbf))) {
      return true;
    }
    return false;
  }
  // 2byte char : U+000080 〜 U+0007FF
  if ((charCode & static_cast<uint32_t>(0xffffff00)) > 0) {
    if ((charCode & static_cast<uint32_t>(0x0000e000)) ==
            static_cast<uint32_t>(0x0000c000) &&
        (charCode & static_cast<uint32_t>(0x000000c0)) ==
            static_cast<uint32_t>(0x00000080) &&
        static_cast<uint32_t>(0x0000c280) <= charCode) {
      return true;
    }
    return false;
  }
  // 1byte char : U+000080 〜 U+00007F
  if ((charCode & static_cast<uint32_t>(0xfffffff80)) ==
      static_cast<uint32_t>(0x00000000)) {
    return true;
  }
  return false;
};
int32_t Utf8::toUtf32(const int32_t &charCode_) {
  return toUtf32(charCode_, false);
};
int32_t Utf8::toUtf32(const int32_t &charCode_, const bool &isLE_) {
  uint32_t charCode = (uint32_t)(charCode_);
  if (!isValidCharCode(charCode_)) {
    if (isLE_) {
      return static_cast<int32_t>(0xfdff0000);
    } else {
      return static_cast<int32_t>(0x0000fffd);
    }
  }
  uint32_t charCodeUtf32;
  // 4byte char : U+010000 〜 U+10FFFF
  if ((charCode & static_cast<uint32_t>(0xff000000)) > 0) {
    charCodeUtf32 = ((charCode & static_cast<uint32_t>(0x07000000)) >> 6) |
                    ((charCode & static_cast<uint32_t>(0x003f0000)) >> 4) |
                    ((charCode & static_cast<uint32_t>(0x00003f00)) >> 2) |
                    (charCode & static_cast<uint32_t>(0x0000003f));
    if (isLE_) {
      return Utf32::swapEndianness(charCodeUtf32);
    } else {
      return (int32_t)charCodeUtf32;
    }
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if ((charCode & static_cast<uint32_t>(0xffff0000)) > 0) {
    charCodeUtf32 = ((charCode & static_cast<uint32_t>(0x000f0000)) >> 4) |
                    ((charCode & static_cast<uint32_t>(0x00003f00)) >> 2) |
                    (charCode & static_cast<uint32_t>(0x0000003f));
    if (isLE_) {
      return Utf32::swapEndianness(charCodeUtf32);
    } else {
      return (int32_t)charCodeUtf32;
    }
  }
  // 2byte char : U+000080 〜 U+0007FF
  if ((charCode & static_cast<uint32_t>(0xffffff00)) > 0) {
    charCodeUtf32 = ((charCode & static_cast<uint32_t>(0x00001f00)) >> 2) |
                    (charCode & static_cast<uint32_t>(0x0000003f));
    if (isLE_) {
      return Utf32::swapEndianness(charCodeUtf32);
    } else {
      return (int32_t)charCodeUtf32;
    }
  }
  // 1byte char : U+000080 〜 U+00007F
  charCodeUtf32 = charCode;
  if (isLE_) {
    return Utf32::swapEndianness(charCodeUtf32);
  } else {
    return (int32_t)charCodeUtf32;
  }
};
std::vector<int16_t> Utf8::toUtf16Chunk(const int32_t &charCode_) {
  return toUtf16Chunk(charCode_, false);
};
std::vector<int16_t> Utf8::toUtf16Chunk(const int32_t &charCode_,
                                        const bool &isLE_) {
  return Utf32::toUtf16Chunk(toUtf32(charCode_), false, isLE_);
};
std::vector<char> Utf8::toUtf8Chunk(const int32_t &charCode_) {
  std::vector<char> chunk;
  if (isNullCharCode(charCode_)) {
    return chunk;
  }
  chunk.reserve(4);
  if (!isValidCharCode(charCode_)) {
    chunk.push_back(static_cast<char>(0xef));
    chunk.push_back(static_cast<char>(0xbf));
    chunk.push_back(static_cast<char>(0xbd));
    return chunk;
  }
  uint32_t charCode = (uint32_t)(charCode_);
  // 4byte char : U+010000 〜 U+10FFFF
  if ((charCode & static_cast<uint32_t>(0xff000000)) > 0) {
    chunk.push_back((char)(charCode >> 24));
    chunk.push_back((char)(charCode >> 16));
    chunk.push_back((char)(charCode >> 8));
    chunk.push_back((char)(charCode & static_cast<char>(0xff)));
    return chunk;
  }
  // 3byte char : U+000800 〜 U+00FFFF
  if ((charCode & static_cast<uint32_t>(0xffff0000)) > 0) {
    chunk.push_back((char)(charCode >> 16));
    chunk.push_back((char)(charCode >> 8));
    chunk.push_back((char)(charCode & static_cast<char>(0xff)));
    return chunk;
  }
  // 2byte char : U+000080 〜 U+0007FF
  if ((charCode & static_cast<uint32_t>(0xffffff00)) > 0) {
    chunk.push_back((char)(charCode >> 8));
    chunk.push_back((char)(charCode & static_cast<char>(0xff)));
    return chunk;
  }
  // 1byte char : U+000080 〜 U+00007F
  chunk.push_back((char)(charCode & static_cast<char>(0xff)));
  return chunk;
};
std::string Utf8::toString(const int32_t &charCode_) {
  if (isBom(charCode_)) {
    return "";
  }
  std::vector<char> chunk = toUtf8Chunk(charCode_);
  return std::string(chunk.begin(), chunk.end());
};
