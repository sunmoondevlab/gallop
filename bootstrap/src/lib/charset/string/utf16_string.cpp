
#include "charset/string/utf16_string.hpp"
#include "charset/char_code/utf16_char_code.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "io/stream/utf16_input_stream.hpp"
#include "io/stream/utf16_output_stream.hpp"
#include "io/stream/utf32_output_stream.hpp"
#include "io/stream/utf8_output_stream.hpp"

using namespace gallop::CharSet::String;
using namespace gallop::IO::Stream;

bool Utf16::isNullString(const std::vector<int16_t> &u16data_) {
  return isNullString(u16data_, false);
};
bool Utf16::isNullString(const std::vector<int16_t> &u16data_,
                         const bool &isLE_) {
  Utf16InputStream uis(u16data_);
  if (uis.size() >= 1 && CharCode::Utf16::isBom(uis.read(), isLE_)) {
    return u16data_.size() == 1;
  }
  return u16data_.size() == 0;
};
bool Utf16::isValidString(const std::vector<int16_t> &u16data_) {
  return isValidString(u16data_, false);
};
bool Utf16::isValidString(const std::vector<int16_t> &u16data_,
                          const bool &isLE_) {
  Utf16InputStream uis(u16data_);
  return isValidString(uis, isLE_);
};
bool Utf16::isValidString(const Utf16InputStream &uis_, const bool &isLE_) {
  Utf16InputStream uis = uis_;
  int16_t charCode;
  int32_t charCode32;
  size_t asciiCount = 0, mbCount = 0, oeAsciiCount = 0, spCount = 0;
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (CharCode::Utf16::isLowSurrogate(charCode, isLE_)) {
      return false;
    }
    // U+010000　〜　U+10FFFF
    if (CharCode::Utf16::isHighSurrogate(charCode, isLE_)) {
      uis.undo();
      charCode32 = uis.readByte4();
      if (!CharCode::Utf16::isSurrogatePair(charCode32, isLE_)) {
        return false;
      }
      spCount++;
    } else {
      if (CharCode::Utf16::isNewLine(charCode, !isLE_)) {
        return false;
      } else if (CharCode::Utf16::isAscii(charCode, isLE_)) {
        asciiCount++;
      } else if (CharCode::Utf16::isAscii(charCode, !isLE_)) {
        oeAsciiCount++;
      } else {
        mbCount++;
      }
    }
  }
  return ((spCount + asciiCount + mbCount) > oeAsciiCount);
};
std::vector<char> Utf16::toUtf8Data(const std::vector<int16_t> &u16data_) {
  return toUtf8Data(u16data_, false, false);
};
std::vector<char> Utf16::toUtf8Data(const std::vector<int16_t> &u16data_,
                                    const bool &isLE_) {
  return toUtf8Data(u16data_, isLE_, false);
};
std::vector<char> Utf16::toUtf8Data(const std::vector<int16_t> &u16data_,
                                    const bool &isLE_, const bool &hasBom_) {
  std::vector<int32_t> u32data = toUtf32Data(u16data_, isLE_, hasBom_);
  size_t charCodeCount = u32data.size();
  Utf8OutputStream baos;
  baos.reserve(u32data.size() * 4);
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
std::vector<int16_t> Utf16::toUtf16Data(const std::vector<int16_t> &u16data_) {
  return toUtf16Data(u16data_, false, false);
};
std::vector<int16_t> Utf16::toUtf16Data(const std::vector<int16_t> &u16data_,
                                        const bool &isLE_) {
  return toUtf16Data(u16data_, isLE_, false);
};
std::vector<int16_t> Utf16::toUtf16Data(const std::vector<int16_t> &u16data_,
                                        const bool &isLE_,
                                        const bool &hasBom_) {
  return toUtf16Data(u16data_, isLE_, hasBom_, false);
};
std::vector<int16_t> Utf16::toUtf16Data(const std::vector<int16_t> &u16data_,
                                        const bool &isLE_, const bool &hasBom_,
                                        const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  std::vector<int32_t> u32data = toUtf32Data(u16data_, isLE_, hasBom_, isLE_);
  size_t charCodeCount = u32data.size();
  Utf16OutputStream uos(false, isDstLE);
  uos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    uos.write(*(u32dataPtr + pos));
  }
  return uos.data();
};
std::vector<int32_t> Utf16::toUtf32Data(const std::vector<int16_t> &u16data_) {
  return toUtf32Data(u16data_, false, false);
};
std::vector<int32_t> Utf16::toUtf32Data(const std::vector<int16_t> &u16data_,
                                        const bool &isLE_) {
  return toUtf32Data(u16data_, isLE_, false);
};
std::vector<int32_t> Utf16::toUtf32Data(const std::vector<int16_t> &u16data_,
                                        const bool &isLE_,
                                        const bool &hasBom_) {
  return toUtf32Data(u16data_, isLE_, hasBom_, false);
};
std::vector<int32_t> Utf16::toUtf32Data(const std::vector<int16_t> &u16data_,
                                        const bool &isLE_, const bool &hasBom_,
                                        const bool &isSwapEndianness_) {
  bool isDstLE = isSwapEndianness_ ? !isLE_ : isLE_;
  Utf16InputStream uis(u16data_);
  Utf32OutputStream uos(false, isDstLE);
  int16_t charCode;
  int32_t charCode32;
  uos.reserve(u16data_.size());
  if (hasBom_) {
    uos.write(static_cast<int32_t>(0x0000feff));
  }
  while (uis.hasReadable()) {
    charCode = uis.read();
    if (CharCode::Utf16::isLowSurrogate(charCode, isLE_)) {
      uos.write(static_cast<int32_t>(0x0000fffd));
    }
    // U+010000　〜　U+10FFFF
    else if (CharCode::Utf16::isHighSurrogate(charCode, isLE_)) {
      if (uis.readable()) {
        uis.undo();
        charCode32 = uis.readByte4();
        if (!CharCode::Utf16::isSurrogatePair(charCode32, isLE_)) {
          uis.undo();
          uos.write(static_cast<int32_t>(0x0000fffd));
        } else {
          uos.write(CharCode::Utf16::toUtf32(charCode32, isLE_, isLE_));
        }
      } else {
        uos.write(static_cast<int32_t>(0x0000fffd));
      }
    } else {
      if (CharCode::Utf16::isNewLine(charCode, !isLE_)) {
        uos.write(static_cast<int32_t>(0x0000fffd));
      } else {
        if (!hasBom_ && uos.stringLen() == 0 &&
            CharCode::Utf16::isBom(charCode, isLE_)) {
          continue;
        }
        uos.write(CharCode::Utf16::toUtf32(charCode, isLE_, isLE_));
      }
    }
  }
  return uos.data();
};
std::string Utf16::toUtf8String(const std::vector<int16_t> &u16data_) {
  return toUtf8String(u16data_, false);
};
std::string Utf16::toUtf8String(const std::vector<int16_t> &u16data_,
                                const bool &isLE_) {
  std::vector<int32_t> u32data = toUtf32Data(u16data_, isLE_, false, isLE_);
  size_t charCodeCount = u32data.size();
  Utf8OutputStream baos;
  baos.reserve(u32data.size() * 4);
  const int32_t *u32dataPtr = u32data.data();
  for (size_t pos = 0; pos < charCodeCount; pos++) {
    baos.write(*(u32dataPtr + pos));
  }
  return baos.toString();
};
