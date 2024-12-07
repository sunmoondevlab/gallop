// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/string/utf8_string.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

using namespace gallop::CharSet::String;
using namespace gallop::IO::Stream;

bool Utf8::isNullString(const std::string &u8string_) {
  return u8string_ == "";
};
bool Utf8::isNullString(const std::vector<char> &u8data_) {
  Utf8InputStream uis(u8data_);
  while (uis.hasReadable()) {
    uis.markCurrent();
    if (CharCode::Utf8::isBom(uis.readByte3())) {
      continue;
    } else {
      uis.rewindToMark();
      break;
    }
  }
  return !uis.hasReadable();
};
bool Utf8::isValidString(const std::string &u8string_) {
  Utf8InputStream uis(std::vector<char>(u8string_.begin(), u8string_.end()));
  return isValidString(uis);
};
bool Utf8::isValidString(const std::vector<char> &u8data_) {
  Utf8InputStream uis(u8data_);
  return isValidString(uis);
};
bool Utf8::isValidString(const Utf8InputStream &uis_) {
  Utf8InputStream uis = uis_;
  uis.rewind();
  int32_t charCode;
  while (uis.hasReadable()) {
    switch (CharCode::Utf8::utf8FetchLength(uis.current())) {
    // U+000000　〜　U+00007F
    case 1:
      uis.read();
      break;
    // U+000080　〜　U+0007FF
    case 2:
      if (uis.readable() < 2) {
        return false;
      }
      charCode = uis.readByte2();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        return false;
      }
      break;
    // U+000800　〜　U+00FFFF
    case 3:
      if (uis.readable() < 3) {
        return false;
      }
      charCode = uis.readByte3();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        return false;
      }
      break;
    // U+010000　〜　U+10FFFF
    case 4:
      if (uis.readable() < 4) {
        return false;
      }
      charCode = uis.readByte4();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        return false;
      }
      break;
    default:
      return false;
    }
  }
  return true;
};
bool Utf8::isAsciiString(const std::string &u8string_) {
  return isAsciiString(std::vector<char>(u8string_.begin(), u8string_.end()));
};
bool Utf8::isAsciiString(const std::vector<char> &u8data_) {
  Utf8InputStream uis(u8data_);
  return isAsciiString(uis);
};
bool Utf8::isAsciiString(const Utf8InputStream &uis_) {
  Utf8InputStream uis = uis_;
  uis.rewind();
  while (uis.hasReadable()) {
    if (!CharCode::Utf8::isAscii(uis.read())) {
      return false;
    }
  }
  return true;
};
std::vector<char> Utf8::toU8Data(const std::string &u8string_) {
  return toU8Data(std::vector<char>(u8string_.begin(), u8string_.end()), false);
};
std::vector<char> Utf8::toU8Data(const std::string &u8string_,
                                 const bool &hasBom_) {
  return toU8Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                  hasBom_);
};
std::vector<char> Utf8::toU8Data(const std::vector<char> &u8data_) {
  return toU8Data(u8data_, false);
};
std::vector<char> Utf8::toU8Data(const std::vector<char> &u8data_,
                                 const bool &hasBom_) {
  std::vector<int32_t> u32data = toU32Data(u8data_, false, hasBom_);
  size_t dataSize = u32data.size();
  Utf8OutputStream uos;
  uos.reserve(u8data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int16_t> Utf8::toU16Data(const std::string &u8string_) {
  return toU16Data(std::vector<char>(u8string_.begin(), u8string_.end()), false,
                   false);
};
std::vector<int16_t> Utf8::toU16Data(const std::string &u8string_,
                                     const bool &isDstLe_) {
  return toU16Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                   isDstLe_, false);
};
std::vector<int16_t> Utf8::toU16Data(const std::string &u8string_,
                                     const bool &isDstLe_,
                                     const bool &hasBom_) {
  return toU16Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                   isDstLe_, hasBom_);
};
std::vector<int16_t> Utf8::toU16Data(const std::vector<char> &u8data_) {
  return toU16Data(u8data_, false, false);
};
std::vector<int16_t> Utf8::toU16Data(const std::vector<char> &u8data_,
                                     const bool &isDstLe_) {
  return toU16Data(u8data_, isDstLe_, false);
};
std::vector<int16_t> Utf8::toU16Data(const std::vector<char> &u8data_,
                                     const bool &isDstLe_,
                                     const bool &hasBom_) {
  std::vector<int32_t> u32data = toU32Data(u8data_, false, hasBom_);
  size_t dataSize = u32data.size();
  Utf16OutputStream uos(false, isDstLe_);
  uos.reserve(u8data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < dataSize; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int32_t> Utf8::toU32Data(const std::string &u8string_) {
  return toU32Data(std::vector<char>(u8string_.begin(), u8string_.end()), false,
                   false);
};
std::vector<int32_t> Utf8::toU32Data(const std::string &u8string_,
                                     const bool &isDstLe_) {
  return toU32Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                   isDstLe_, false);
};
std::vector<int32_t> Utf8::toU32Data(const std::string &u8string_,
                                     const bool &isDstLe_,
                                     const bool &hasBom_) {
  return toU32Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                   isDstLe_, hasBom_);
};
std::vector<int32_t> Utf8::toU32Data(const std::vector<char> &u8data_) {
  return toU32Data(u8data_, false, false);
};
std::vector<int32_t> Utf8::toU32Data(const std::vector<char> &u8data_,
                                     const bool &isDstLe_) {
  return toU32Data(u8data_, isDstLe_, false);
};
std::vector<int32_t> Utf8::toU32Data(const std::vector<char> &u8data_,
                                     const bool &isDstLe_,
                                     const bool &hasBom_) {
  Utf8InputStream uis(u8data_);
  Utf32OutputStream uos(false, isDstLe_);
  int32_t charCode;
  bool isInvalidContinue = false;
  uos.reserve(u8data_.size() * 2);
  if (hasBom_) {
    uos.writeBom();
  }
  while (uis.hasReadable()) {
    switch (CharCode::Utf8::utf8FetchLength(uis.current())) {
    // U+000000　〜　U+00007F
    case 1:
      isInvalidContinue = false;
      charCode = uis.read();
      uos.write(charCode);
      break;
    // U+000080　〜　U+0007FF
    case 2:
      if (uis.readable() < 2) {
        uos.writeReplacementChar();
      }
      charCode = uis.readByte2();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        uos.writeReplacementChar();
        uis.rewind(1);
        isInvalidContinue = true;
        break;
      }
      isInvalidContinue = false;
      uos.write(CharCode::Utf8::toU32(charCode));
      break;
    // U+000800　〜　U+00FFFF
    case 3:
      if (uis.readable() < 2) {
        uos.writeReplacementChar();
      }
      charCode = uis.readByte3();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        uos.writeReplacementChar();
        uis.rewind(2);
        isInvalidContinue = true;
        break;
      }
      isInvalidContinue = false;
      if (!hasBom_ && uos.stringLen() == 0 && CharCode::Utf8::isBom(charCode)) {
        break;
      }
      uos.write(CharCode::Utf8::toU32(charCode));
      break;
    // U+100000　〜　U+10FFFF
    case 4:
      if (uis.readable() < 2) {
        uos.writeReplacementChar();
      }
      charCode = uis.readByte4();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        uos.writeReplacementChar();
        uis.rewind(3);
        isInvalidContinue = true;
        break;
      }
      isInvalidContinue = false;
      uos.write(CharCode::Utf8::toU32(charCode));
      break;
    default:
      charCode = uis.read();
      if (!isInvalidContinue || !CharCode::Utf8::isContinuationByte(charCode)) {
        isInvalidContinue = false;
        uos.writeReplacementChar();
      }
    }
  }
  return uos.data();
};
std::string Utf8::toU8String(const std::string &u8string_) {
  return toU8String(std::vector<char>(u8string_.begin(), u8string_.end()));
};
std::string Utf8::toU8String(const std::vector<char> &u8data_) {
  std::vector<char> u8data = toU8Data(u8data_);
  return std::string(u8data.begin(), u8data.end());
};
std::u16string Utf8::toU16String(const std::string &u8string_) {
  return toU16String(std::vector<char>(u8string_.begin(), u8string_.end()));
};
std::u16string Utf8::toU16String(const std::vector<char> &u8data_) {
  std::vector<int16_t> u16data = toU16Data(u8data_);
  return std::u16string(u16data.begin(), u16data.end());
};
std::u32string Utf8::toU32String(const std::string &u8string_) {
  return toU32String(std::vector<char>(u8string_.begin(), u8string_.end()));
};
std::u32string Utf8::toU32String(const std::vector<char> &u8data_) {
  std::vector<int32_t> u32data = toU32Data(u8data_);
  return std::u32string(u32data.begin(), u32data.end());
};
