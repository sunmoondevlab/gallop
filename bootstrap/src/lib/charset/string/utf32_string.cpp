// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.

#include "charset/string/utf32_string.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_input_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

using namespace gallop::CharSet::String;
using namespace gallop::IO::Stream;

bool Utf32::isNullString(const std::vector<int32_t> &u32data_) {
  return isNullString(u32data_, false);
};
bool Utf32::isNullString(const std::vector<int32_t> &u32data_,
                         const bool &isLE_) {
  Utf32InputStream uis(u32data_);
  if (uis.size() >= 1 && CharCode::Utf32::isBom(uis.read(), isLE_)) {
    return u32data_.size() == 1;
  }
  return u32data_.size() == 0;
};
bool Utf32::isValidString(const std::vector<int32_t> &u32data_) {
  return isValidString(u32data_, false);
};
bool Utf32::isValidString(const std::vector<int32_t> &u32data_,
                          const bool &isLE_) {
  Utf32InputStream uis(u32data_);
  return isValidString(uis, isLE_);
};
bool Utf32::isValidString(const Utf32InputStream &uis_, const bool &isLE_) {
  Utf32InputStream uis = uis_;
  int32_t charCode;
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (!CharCode::Utf32::isValidCharCode(charCode, isLE_)) {
      return false;
    }
  }
  return true;
};
std::vector<char> Utf32::toUtf8Data(const std::vector<int32_t> &u32data_) {
  return toUtf8Data(u32data_, false, false);
};
std::vector<char> Utf32::toUtf8Data(const std::vector<int32_t> &u32data_,
                                    const bool &isLE_) {
  return toUtf8Data(u32data_, isLE_, false);
};
std::vector<char> Utf32::toUtf8Data(const std::vector<int32_t> &u32data_,
                                    const bool &isLE_, const bool &hasBom_) {
  std::vector<int32_t> u32data = toUtf32Data(u32data_, isLE_, hasBom_);
  size_t charCodeCount = u32data.size();
  Utf8OutputStream baos;
  baos.reserve(u32data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    if (isLE_) {
      baos.write(CharCode::Utf32::swapEndianness(*(u32dataPtr + pos)));
    } else {
      baos.write(*(u32dataPtr + pos));
    }
  }
  return baos.data();
};
std::vector<int16_t> Utf32::toUtf16Data(const std::vector<int32_t> &u32data_) {
  return toUtf16Data(u32data_, false, false);
};
std::vector<int16_t> Utf32::toUtf16Data(const std::vector<int32_t> &u32data_,
                                        const bool &isLE_) {
  return toUtf16Data(u32data_, isLE_, false);
};
std::vector<int16_t> Utf32::toUtf16Data(const std::vector<int32_t> &u32data_,
                                        const bool &isLE_,
                                        const bool &hasBom_) {
  return toUtf16Data(u32data_, isLE_, hasBom_, false);
};
std::vector<int16_t> Utf32::toUtf16Data(const std::vector<int32_t> &u32data_,
                                        const bool &isLE_, const bool &hasBom_,
                                        const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  std::vector<int32_t> u32data = toUtf32Data(u32data_, isLE_, hasBom_, isLE_);
  size_t charCodeCount = u32data.size();
  Utf16OutputStream uos(false, isDstLE);
  uos.reserve(u32data_.size() * 2);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int32_t> Utf32::toUtf32Data(const std::vector<int32_t> &u32data_) {
  return toUtf32Data(u32data_, false, false);
};
std::vector<int32_t> Utf32::toUtf32Data(const std::vector<int32_t> &u32data_,
                                        const bool &isLE_) {
  return toUtf32Data(u32data_, isLE_, false);
};
std::vector<int32_t> Utf32::toUtf32Data(const std::vector<int32_t> &u32data_,
                                        const bool &isLE_,
                                        const bool &hasBom_) {
  return toUtf32Data(u32data_, isLE_, hasBom_, false);
};
std::vector<int32_t> Utf32::toUtf32Data(const std::vector<int32_t> &u32data_,
                                        const bool &isLE_, const bool &hasBom_,
                                        const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  Utf32InputStream uis(u32data_);
  Utf32OutputStream uos(false, isDstLE);
  int32_t charCode;
  uos.reserve(u32data_.size() * 2);
  if (hasBom_) {
    uos.write(static_cast<int32_t>(0x0000feff));
  }
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (!CharCode::Utf32::isValidCharCode(charCode, isLE_)) {
      uos.write(static_cast<int32_t>(0x0000fffd));
      continue;
    }
    if (!hasBom_ && uos.stringLen() == 0 &&
        CharCode::Utf32::isBom(charCode, isLE_)) {
      continue;
    }
    if (isLE_) {
      charCode = CharCode::Utf32::swapEndianness(charCode);
    }
    uos.write(charCode);
  }
  return uos.data();
};
std::string Utf32::toUtf8String(const std::vector<int32_t> &u32data_) {
  return toUtf8String(u32data_, false);
};
std::string Utf32::toUtf8String(const std::vector<int32_t> &u32data_,
                                const bool &isLE_) {
  std::vector<int32_t> u32data = toUtf32Data(u32data_, isLE_, false, isLE_);
  size_t charCodeCount = u32data.size();
  Utf8OutputStream baos;
  baos.reserve(u32data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    baos.write(*(u32dataPtr + pos));
  }
  return baos.toString();
};
