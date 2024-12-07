// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/string/utf32_string.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

using namespace gallop::CharSet::String;
using namespace gallop::IO::Stream;

bool Utf32::isNullString(const std::u32string &u32string_) {
  return u32string_ == U"";
};
bool Utf32::isNullString(const std::vector<int32_t> &u32data_) {
  return isNullString(u32data_, false);
};
bool Utf32::isNullString(const std::vector<int32_t> &u32data_,
                         const bool &isSrcLe_) {
  Utf32InputStream uis(u32data_);
  while (uis.hasReadable()) {
    if (CharCode::Utf32::isBom(uis.current(), isSrcLe_)) {
      uis.read();
      continue;
    } else {
      break;
    }
  }
  return !uis.readable();
};
bool Utf32::isValidString(const std::u32string &u32string_) {
  Utf32InputStream uis(
      std::vector<int32_t>(u32string_.begin(), u32string_.end()));
  return isValidString(uis, false);
};
bool Utf32::isValidString(const std::vector<int32_t> &u32data_) {
  Utf32InputStream uis(u32data_);
  return isValidString(uis, false);
};
bool Utf32::isValidString(const std::vector<int32_t> &u32data_,
                          const bool &isSrcLe_) {
  Utf32InputStream uis(u32data_);
  return isValidString(uis, isSrcLe_);
};
bool Utf32::isValidString(const Utf32InputStream &uis_, const bool &isSrcLe_) {
  Utf32InputStream uis = uis_;
  uis.rewind();
  int32_t charCode;
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (!CharCode::Utf32::isValidCharCode(charCode, isSrcLe_)) {
      return false;
    }
  }
  return true;
};
bool Utf32::isAsciiString(const std::u32string &u32string_) {
  Utf32InputStream uis(
      std::vector<int32_t>(u32string_.begin(), u32string_.end()));
  return isAsciiString(uis, false);
};
bool Utf32::isAsciiString(const std::vector<int32_t> &u32data_) {
  Utf32InputStream uis(u32data_);
  return isAsciiString(uis, false);
};
bool Utf32::isAsciiString(const std::vector<int32_t> &u32data_,
                          const bool &isSrcLe_) {
  Utf32InputStream uis(u32data_);
  return isAsciiString(uis, isSrcLe_);
};
bool Utf32::isAsciiString(const Utf32InputStream &uis_, const bool &isSrcLe_) {
  Utf32InputStream uis = uis_;
  uis.rewind();
  while (uis.hasReadable()) {
    if (!CharCode::Utf32::isAscii(uis.read(), isSrcLe_)) {
      return false;
    }
  }
  return true;
};
std::vector<char> Utf32::toU8Data(const std::u32string &u32string_) {
  return toU8Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                  false, false);
};
std::vector<char> Utf32::toU8Data(const std::u32string &u32string_,
                                  const bool &hasBom_) {
  return toU8Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                  false, hasBom_);
};
std::vector<char> Utf32::toU8Data(const std::vector<int32_t> &u32data_) {
  return toU8Data(u32data_, false, false);
};
std::vector<char> Utf32::toU8Data(const std::vector<int32_t> &u32data_,
                                  const bool &isSrcLe_) {
  return toU8Data(u32data_, isSrcLe_, false);
};
std::vector<char> Utf32::toU8Data(const std::vector<int32_t> &u32data_,
                                  const bool &isSrcLe_, const bool &hasBom_) {
  std::vector<int32_t> u32data = toU32Data(u32data_, isSrcLe_, false, hasBom_);
  size_t dataSize = u32data.size();
  Utf8OutputStream uos;
  uos.reserve(u32data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int16_t> Utf32::toU16Data(const std::u32string &u32string_) {
  return toU16Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                   false, false, false);
};
std::vector<int16_t> Utf32::toU16Data(const std::u32string &u32string_,
                                      const bool &hasBom_) {
  return toU16Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                   false, false, hasBom_);
};
std::vector<int16_t> Utf32::toU16Data(const std::u32string &u32string_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  return toU16Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                   false, isDstLe_, hasBom_);
};
std::vector<int16_t> Utf32::toU16Data(const std::vector<int32_t> &u32data_) {
  return toU16Data(u32data_, false, false, false);
};
std::vector<int16_t> Utf32::toU16Data(const std::vector<int32_t> &u32data_,
                                      const bool &isSrcLe_) {
  return toU16Data(u32data_, isSrcLe_, isSrcLe_, false);
};
std::vector<int16_t> Utf32::toU16Data(const std::vector<int32_t> &u32data_,
                                      const bool &isSrcLe_,
                                      const bool &hasBom_) {
  return toU16Data(u32data_, isSrcLe_, isSrcLe_, hasBom_);
};
std::vector<int16_t> Utf32::toU16Data(const std::vector<int32_t> &u32data_,
                                      const bool &isSrcLe_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  std::vector<int32_t> u32data = toU32Data(u32data_, isSrcLe_, false, hasBom_);
  size_t dataSize = u32data.size();
  Utf16OutputStream uos(false, isDstLe_);
  uos.reserve(u32data_.size() * 2);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int32_t> Utf32::toU32Data(const std::u32string &u32string_) {
  return toU32Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                   false, false, false);
};
std::vector<int32_t> Utf32::toU32Data(const std::u32string &u32string_,
                                      const bool &hasBom_) {
  return toU32Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                   false, false, hasBom_);
};
std::vector<int32_t> Utf32::toU32Data(const std::u32string &u32string_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  return toU32Data(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                   false, isDstLe_, hasBom_);
};
std::vector<int32_t> Utf32::toU32Data(const std::vector<int32_t> &u32data_) {
  return toU32Data(u32data_, false, false, false);
};
std::vector<int32_t> Utf32::toU32Data(const std::vector<int32_t> &u32data_,
                                      const bool &isSrcLe_) {
  return toU32Data(u32data_, isSrcLe_, isSrcLe_, false);
};
std::vector<int32_t> Utf32::toU32Data(const std::vector<int32_t> &u32data_,
                                      const bool &isSrcLe_,
                                      const bool &hasBom_) {
  return toU32Data(u32data_, isSrcLe_, isSrcLe_, hasBom_);
};
std::vector<int32_t> Utf32::toU32Data(const std::vector<int32_t> &u32data_,
                                      const bool &isSrcLe_,
                                      const bool &isDstLe_,
                                      const bool &hasBom_) {
  Utf32InputStream uis(u32data_);
  Utf32OutputStream uos(isSrcLe_, isDstLe_);
  int32_t charCode;
  uos.reserve(u32data_.size() * 2);
  if (hasBom_) {
    uos.writeBom();
  }
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (!CharCode::Utf32::isValidCharCode(charCode, isSrcLe_)) {
      uos.writeReplacementChar();
      continue;
    }
    if (!hasBom_ && uos.stringLen() == 0 &&
        CharCode::Utf32::isBom(charCode, isSrcLe_)) {
      continue;
    }
    uos.write(charCode);
  }
  return uos.data();
};
std::string Utf32::toU8String(const std::u32string &u32string_) {
  return toU8String(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                    false);
};
std::string Utf32::toU8String(const std::vector<int32_t> &u32data_) {
  return toU8String(u32data_, false);
};
std::string Utf32::toU8String(const std::vector<int32_t> &u32data_,
                              const bool &isSrcLe_) {
  std::vector<int32_t> u32data = toU32Data(u32data_, isSrcLe_, false, false);
  size_t dataSize = u32data.size();
  Utf8OutputStream uos;
  uos.reserve(u32data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.toU8String();
};
std::u16string Utf32::toU16String(const std::u32string &u32string_) {
  return toU16String(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                     false);
};
std::u16string Utf32::toU16String(const std::vector<int32_t> &u32data_) {
  return toU16String(u32data_, false);
};
std::u16string Utf32::toU16String(const std::vector<int32_t> &u32data_,
                                  const bool &isSrcLe_) {
  std::vector<int32_t> u32data = toU32Data(u32data_, isSrcLe_, false, false);
  size_t dataSize = u32data.size();
  Utf16OutputStream uos;
  uos.reserve(u32data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.toU16String();
};
std::u32string Utf32::toU32String(const std::u32string &u32string_) {
  return toU32String(std::vector<int32_t>(u32string_.begin(), u32string_.end()),
                     false);
};
std::u32string Utf32::toU32String(const std::vector<int32_t> &u32data_) {
  return toU32String(u32data_, false);
};
std::u32string Utf32::toU32String(const std::vector<int32_t> &u32data_,
                                  const bool &isSrcLe_) {
  std::vector<int32_t> u32data = toU32Data(u32data_, isSrcLe_, false, false);
  size_t dataSize = u32data.size();
  Utf32OutputStream uos;
  uos.reserve(u32data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.toU32String();
};
