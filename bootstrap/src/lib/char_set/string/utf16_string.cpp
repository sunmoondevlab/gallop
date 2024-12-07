// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/string/utf16_string.hpp"

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

using namespace gallop::CharSet::String;
using namespace gallop::IO::Stream;

bool Utf16::isNullString(const std::u16string &u16string_) {
  return u16string_ == u"";
};
bool Utf16::isNullString(const std::vector<int16_t> &u16data_) {
  return isNullString(u16data_, false);
};
bool Utf16::isNullString(const std::vector<int16_t> &u16data_,
                         const bool &isSrcLe_) {
  Utf16InputStream uis(u16data_);
  while (uis.hasReadable()) {
    if (CharCode::Utf16::isBom(uis.current(), isSrcLe_)) {
      uis.read();
      continue;
    } else {
      break;
    }
  }
  return !uis.readable();
};
bool Utf16::isValidString(const std::u16string &u16string_) {
  Utf16InputStream uis(
      std::vector<int16_t>(u16string_.begin(), u16string_.end()));
  return isValidString(uis, false);
};
bool Utf16::isValidString(const std::vector<int16_t> &u16data_) {
  Utf16InputStream uis(u16data_);
  return isValidString(uis, false);
};
bool Utf16::isValidString(const std::vector<int16_t> &u16data_,
                          const bool &isSrcLe_) {
  Utf16InputStream uis(u16data_);
  return isValidString(uis, isSrcLe_);
};
bool Utf16::isValidString(const Utf16InputStream &uis_, const bool &isSrcLe_) {
  Utf16InputStream uis = uis_;
  uis.rewind();
  int16_t charCode;
  int32_t charCode32;
  size_t asciiCount = 0, mbCount = 0, oeAsciiCount = 0, spCount = 0;
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (!CharCode::Utf16::isValidCharCode(charCode, isSrcLe_)) {
      return false;
    }
    // U+010000　〜　U+10FFFF
    if (CharCode::Utf16::isHighSurrogate(charCode, isSrcLe_)) {
      uis.undo();
      charCode32 = uis.readByte4();
      if (!CharCode::Utf16::isSurrogatePair(charCode32, isSrcLe_)) {
        return false;
      }
      spCount++;
    } else {
      if (CharCode::Utf16::isAscii(charCode, isSrcLe_)) {
        asciiCount++;
      } else if (CharCode::Utf16::isAscii(charCode, !isSrcLe_)) {
        oeAsciiCount++;
      } else {
        mbCount++;
      }
    }
  }
  return ((spCount + asciiCount + mbCount) > oeAsciiCount);
};
bool Utf16::isAsciiString(const std::u16string &u16string_) {
  Utf16InputStream uis(
      std::vector<int16_t>(u16string_.begin(), u16string_.end()));
  return isAsciiString(uis, false);
};
bool Utf16::isAsciiString(const std::vector<int16_t> &u16data_) {
  Utf16InputStream uis(u16data_);
  return isAsciiString(uis, false);
};
bool Utf16::isAsciiString(const std::vector<int16_t> &u16data_,
                          const bool &isSrcLe_) {
  Utf16InputStream uis(u16data_);
  return isAsciiString(uis, isSrcLe_);
};
bool Utf16::isAsciiString(const Utf16InputStream &uis_, const bool &isSrcLe_) {
  Utf16InputStream uis = uis_;
  uis.rewind();
  while (uis.hasReadable()) {
    if (!CharCode::Utf16::isAscii(uis.read(), isSrcLe_)) {
      return false;
    }
  }
  return true;
};
std::vector<char> Utf16::toU8Data(const std::u16string &u16string_) {
  return toU8Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                  false, false);
};
std::vector<char> Utf16::toU8Data(const std::u16string &u16string_,
                                  const bool &hasBom_) {
  return toU8Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                  false, hasBom_);
};
std::vector<char> Utf16::toU8Data(const std::vector<int16_t> &u16data_) {
  return toU8Data(u16data_, false, false);
};
std::vector<char> Utf16::toU8Data(const std::vector<int16_t> &u16data_,
                                  const bool &isSrcLe_) {
  return toU8Data(u16data_, isSrcLe_, false);
};
std::vector<char> Utf16::toU8Data(const std::vector<int16_t> &u16data_,
                                  const bool &isSrcLe_, const bool &hasBom_) {
  std::vector<int32_t> u32data = toU32Data(u16data_, isSrcLe_, false, hasBom_);
  size_t dataSize = u32data.size();
  Utf8OutputStream uos;
  uos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int16_t> Utf16::toU16Data(const std::u16string &u16string_) {
  return toU16Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                   false, false, false);
};
std::vector<int16_t> Utf16::toU16Data(const std::u16string &u16string_,
                                      const bool &hasBom_) {
  return toU16Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                   false, false, hasBom_);
};
std::vector<int16_t> Utf16::toU16Data(const std::u16string &u16string_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  return toU16Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                   false, isDstLe_, hasBom_);
};
std::vector<int16_t> Utf16::toU16Data(const std::vector<int16_t> &u16data_) {
  return toU16Data(u16data_, false, false, false);
};
std::vector<int16_t> Utf16::toU16Data(const std::vector<int16_t> &u16data_,
                                      const bool &isSrcLe_) {
  return toU16Data(u16data_, isSrcLe_, isSrcLe_, false);
};
std::vector<int16_t> Utf16::toU16Data(const std::vector<int16_t> &u16data_,
                                      const bool &isSrcLe_,
                                      const bool &hasBom_) {
  return toU16Data(u16data_, isSrcLe_, isSrcLe_, hasBom_);
};
std::vector<int16_t> Utf16::toU16Data(const std::vector<int16_t> &u16data_,
                                      const bool &isSrcLe_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  std::vector<int32_t> u32data = toU32Data(u16data_, isSrcLe_, false, hasBom_);
  size_t dataSize = u32data.size();
  Utf16OutputStream uos(false, isDstLe_);
  uos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int32_t> Utf16::toU32Data(const std::u16string &u16string_) {
  return toU32Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                   false, false, false);
};
std::vector<int32_t> Utf16::toU32Data(const std::u16string &u16string_,
                                      const bool &hasBom_) {
  return toU32Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                   false, false, hasBom_);
};
std::vector<int32_t> Utf16::toU32Data(const std::u16string &u16string_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  return toU32Data(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                   false, isDstLe_, hasBom_);
};
std::vector<int32_t> Utf16::toU32Data(const std::vector<int16_t> &u16data_) {
  return toU32Data(u16data_, false, false, false);
};
std::vector<int32_t> Utf16::toU32Data(const std::vector<int16_t> &u16data_,
                                      const bool &isSrcLe_) {
  return toU32Data(u16data_, isSrcLe_, isSrcLe_, false);
};
std::vector<int32_t> Utf16::toU32Data(const std::vector<int16_t> &u16data_,
                                      const bool &isSrcLe_,
                                      const bool &hasBom_) {
  return toU32Data(u16data_, isSrcLe_, isSrcLe_, hasBom_);
};
std::vector<int32_t> Utf16::toU32Data(const std::vector<int16_t> &u16data_,
                                      const bool &isSrcLe_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  Utf16InputStream uis(u16data_);
  Utf32OutputStream uos(isSrcLe_, isDstLe_);
  int16_t charCode;
  int32_t charCode32;
  uos.reserve(u16data_.size());
  if (hasBom_) {
    uos.writeBom();
  }
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (CharCode::Utf16::isLowSurrogate(charCode, isSrcLe_)) {
      uos.writeReplacementChar();
    }
    // U+010000　〜　U+10FFFF
    else if (CharCode::Utf16::isHighSurrogate(charCode, isSrcLe_)) {
      if (uis.readable()) {
        uis.undo();
        charCode32 = uis.readByte4();
        if (!CharCode::Utf16::isSurrogatePair(charCode32, isSrcLe_)) {
          uis.undo();
          uos.writeReplacementChar();
        } else {
          uos.write(CharCode::Utf16::toU32(charCode32, isSrcLe_, isSrcLe_));
        }
      } else {
        uos.writeReplacementChar();
      }
    } else {
      if (CharCode::Utf16::isLineBreak(charCode, !isSrcLe_)) {
        uos.writeReplacementChar();
      } else {
        if (!hasBom_ && uos.stringLen() == 0 &&
            CharCode::Utf16::isBom(charCode, isSrcLe_)) {
          continue;
        }
        uos.write(CharCode::Utf16::toU32(charCode, isSrcLe_, isSrcLe_));
      }
    }
  }
  return uos.data();
};
std::string Utf16::toU8String(const std::u16string &u16string_) {
  return toU8String(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                    false);
};
std::string Utf16::toU8String(const std::vector<int16_t> &u16data_) {
  return toU8String(u16data_, false);
};
std::string Utf16::toU8String(const std::vector<int16_t> &u16data_,
                              const bool &isSrcLe_) {
  std::vector<int32_t> u32data = toU32Data(u16data_, isSrcLe_, false, false);
  size_t dataSize = u32data.size();
  Utf8OutputStream uos;
  uos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.toU8String();
};
std::u16string Utf16::toU16String(const std::u16string &u16string_) {
  return toU16String(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                     false);
};
std::u16string Utf16::toU16String(const std::vector<int16_t> &u16data_) {
  return toU16String(u16data_, false);
};
std::u16string Utf16::toU16String(const std::vector<int16_t> &u16data_,
                                  const bool &isSrcLe_) {
  std::vector<int32_t> u32data = toU32Data(u16data_, isSrcLe_, false, false);
  size_t dataSize = u32data.size();
  Utf16OutputStream uos;
  uos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.toU16String();
};
std::u32string Utf16::toU32String(const std::u16string &u16string_) {
  return toU32String(std::vector<int16_t>(u16string_.begin(), u16string_.end()),
                     false);
};
std::u32string Utf16::toU32String(const std::vector<int16_t> &u16data_) {
  return toU32String(u16data_, false);
};
std::u32string Utf16::toU32String(const std::vector<int16_t> &u16data_,
                                  const bool &isSrcLe_) {
  std::vector<int32_t> u32data = toU32Data(u16data_, isSrcLe_, false, false);
  size_t dataSize = u32data.size();
  Utf32OutputStream uos;
  uos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.toU32String();
};
