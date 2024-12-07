
#include "charset/string/utf8_string.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "charset/char_code/utf8_char_code.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_input_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

using namespace gallop::CharSet::String;
using namespace gallop::IO::Stream;

bool Utf8::isNullString(const std::string &u8string_) {
  return u8string_ == "";
};
bool Utf8::isNullString(const std::vector<char> &u8data_) {
  Utf8InputStream bais(u8data_);
  if (bais.size() >= 3 && CharCode::Utf8::isBom(bais.readByte3())) {
    return u8data_.size() == 3;
  }
  return u8data_.size() == 0;
};
bool Utf8::isValidString(const std::string &u8string_) {
  return isValidString(std::vector<char>(u8string_.begin(), u8string_.end()));
};
bool Utf8::isValidString(const std::vector<char> &u8data_) {
  Utf8InputStream bais(u8data_);
  return isValidString(bais);
};
bool Utf8::isValidString(const Utf8InputStream &bais_) {
  Utf8InputStream bais = bais_;
  int32_t charCode;
  while (bais.hasReadable()) {
    switch (CharCode::Utf8::utf8FetchLength(bais.current())) {
    // U+000000　〜　U+00007F
    case 1:
      bais.read();
      break;
    // U+000080　〜　U+0007FF
    case 2:
      if (bais.readable() < 2) {
        return false;
      }
      charCode = (int32_t)(static_cast<int32_t>(0x0000ffff) & bais.readByte2());
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        return false;
      }
      break;
    // U+000800　〜　U+00FFFF
    case 3:
      if (bais.readable() < 3) {
        return false;
      }
      charCode = bais.readByte3();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        return false;
      }
      break;
    // U+010000　〜　U+10FFFF
    case 4:
      if (bais.readable() < 4) {
        return false;
      }
      charCode = bais.readByte4();
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
  Utf8InputStream bais(u8data_);
  return isAsciiString(bais);
};
bool Utf8::isAsciiString(const Utf8InputStream &bais_) {
  Utf8InputStream bais = bais_;
  while (bais.hasReadable()) {
    if (!CharCode::Utf8::isAscii(bais.read())) {
      return false;
    }
  }
  return true;
};
std::vector<char> Utf8::toUtf8Data(const std::string &u8string_) {
  return toUtf8Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                    false);
};
std::vector<char> Utf8::toUtf8Data(const std::string &u8string_,
                                   const bool &hasBom_) {
  return toUtf8Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                    hasBom_);
};
std::vector<char> Utf8::toUtf8Data(const std::vector<char> &u8data_) {
  return toUtf8Data(u8data_, false);
};
std::vector<char> Utf8::toUtf8Data(const std::vector<char> &u8data_,
                                   const bool &hasBom_) {
  std::vector<int32_t> u32data = toUtf32Data(u8data_, false, hasBom_);
  size_t charCodeCount = u32data.size();
  Utf8OutputStream baos;
  baos.reserve(u8data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    baos.write(*(u32dataPtr + pos));
  }
  return baos.data();
};
std::vector<int16_t> Utf8::toUtf16Data(const std::string &u8string_) {
  return toUtf16Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                     false, false);
};
std::vector<int16_t> Utf8::toUtf16Data(const std::string &u8string_,
                                       const bool &isLE_) {
  return toUtf16Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                     isLE_, false);
};
std::vector<int16_t> Utf8::toUtf16Data(const std::string &u8string_,
                                       const bool &isLE_, const bool &hasBom_) {
  return toUtf16Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                     isLE_, hasBom_);
};
std::vector<int16_t> Utf8::toUtf16Data(const std::vector<char> &u8data_) {
  return toUtf16Data(u8data_, false, false);
};
std::vector<int16_t> Utf8::toUtf16Data(const std::vector<char> &u8data_,
                                       const bool &isLE_) {
  return toUtf16Data(u8data_, isLE_, false);
};
std::vector<int16_t> Utf8::toUtf16Data(const std::vector<char> &u8data_,
                                       const bool &isLE_, const bool &hasBom_) {
  std::vector<int32_t> u32data = toUtf32Data(u8data_, false, hasBom_);
  size_t charCodeCount = u32data.size();
  Utf16OutputStream uos(isLE_);
  uos.reserve(u8data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int32_t> Utf8::toUtf32Data(const std::string &u8string_) {
  return toUtf32Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                     false, false);
};
std::vector<int32_t> Utf8::toUtf32Data(const std::string &u8string_,
                                       const bool &isLE_) {
  return toUtf32Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                     isLE_, false);
};
std::vector<int32_t> Utf8::toUtf32Data(const std::string &u8string_,
                                       const bool &isLE_, const bool &hasBom_) {
  return toUtf32Data(std::vector<char>(u8string_.begin(), u8string_.end()),
                     isLE_, hasBom_);
};
std::vector<int32_t> Utf8::toUtf32Data(const std::vector<char> &u8data_) {
  return toUtf32Data(u8data_, false, false);
};
std::vector<int32_t> Utf8::toUtf32Data(const std::vector<char> &u8data_,
                                       const bool &isLE_) {
  return toUtf32Data(u8data_, isLE_, false);
};
std::vector<int32_t> Utf8::toUtf32Data(const std::vector<char> &u8data_,
                                       const bool &isLE_, const bool &hasBom_) {
  Utf8InputStream bais(u8data_);
  Utf32OutputStream uos(isLE_);
  int32_t charCode;
  bool isInvalidContinue = false;
  uos.reserve(u8data_.size() * 2);
  if (hasBom_) {
    uos.write(static_cast<int32_t>(0x0000feff));
  }
  while (bais.hasReadable()) {
    switch (CharCode::Utf8::utf8FetchLength(bais.current())) {
    // U+000000　〜　U+00007F
    case 1:
      isInvalidContinue = false;
      charCode = (int32_t)(static_cast<int32_t>(0x000000ff) & bais.read());
      uos.write(charCode);
      break;
    // U+000080　〜　U+0007FF
    case 2:
      if (bais.readable() < 2) {
        uos.write(static_cast<int32_t>(0x0000fffd));
      }
      charCode = (int32_t)(static_cast<int32_t>(0x0000ffff) & bais.readByte2());
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        uos.write(static_cast<int32_t>(0x0000fffd));
        bais.rewind(1);
        isInvalidContinue = true;
        break;
      }
      isInvalidContinue = false;
      uos.write(CharCode::Utf8::toUtf32(charCode));
      break;
    // U+000800　〜　U+00FFFF
    case 3:
      if (bais.readable() < 2) {
        uos.write(static_cast<int32_t>(0x0000fffd));
      }
      charCode = bais.readByte3();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        uos.write(static_cast<int32_t>(0x0000fffd));
        bais.rewind(2);
        isInvalidContinue = true;
        break;
      }
      isInvalidContinue = false;
      if (!hasBom_ && uos.stringLen() == 0 && CharCode::Utf8::isBom(charCode)) {
        break;
      }
      uos.write(CharCode::Utf8::toUtf32(charCode));
      break;
    // U+100000　〜　U+10FFFF
    case 4:
      if (bais.readable() < 2) {
        uos.write(static_cast<int32_t>(0x0000fffd));
      }
      charCode = bais.readByte4();
      if (!CharCode::Utf8::isValidCharCode(charCode)) {
        uos.write(static_cast<int32_t>(0x0000fffd));
        bais.rewind(3);
        isInvalidContinue = true;
        break;
      }
      isInvalidContinue = false;
      uos.write(CharCode::Utf8::toUtf32(charCode));
      break;
    default:
      charCode = (int32_t)(static_cast<int32_t>(0x000000ff) & bais.read());
      if (!isInvalidContinue || !CharCode::Utf8::isContinuationByte(charCode)) {
        isInvalidContinue = false;
        uos.write(static_cast<int32_t>(0x0000fffd));
      }
    }
  }
  return uos.data();
};
std::string Utf8::toUtf8String(const std::string &u8string_) {
  return toUtf8String(std::vector<char>(u8string_.begin(), u8string_.end()));
};
std::string Utf8::toUtf8String(const std::vector<char> &u8data_) {
  std::vector<int32_t> u32data = toUtf32Data(u8data_, false, false);
  size_t charCodeCount = u32data.size();
  Utf8OutputStream baos;
  baos.reserve(u8data_.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    baos.write(*(u32dataPtr + pos));
  }
  return baos.toString();
};
