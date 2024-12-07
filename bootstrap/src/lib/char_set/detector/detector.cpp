// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "char_set/detector/detector.hpp"

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "char_set/encoding_charset/encoding_charset.hpp"
#include "char_set/string/utf16_string.hpp"
#include "char_set/string/utf32_string.hpp"
#include "char_set/string/utf8_string.hpp"
#include "io/stream/utf16_input_stream.hpp"
#include "io/stream/utf32_input_stream.hpp"
#include "io/stream/utf8_input_stream.hpp"

using namespace gallop::CharSet;
using namespace gallop::IO::Stream;

Detector::Detector(const std::vector<char> &buffer_)
    : charset(EncodingCharsetEnum::Unknown),
      buffer(const_cast<std::vector<char> &>(buffer_)) {
  scanningBuffer();
};
Detector::Detector(const Detector &rhs)
    : charset(rhs.charset), buffer(rhs.buffer) {};

Detector &Detector::operator=(const Detector &rhs) {
  charset = rhs.charset;
  buffer = rhs.buffer;
  return *this;
};

void Detector::scanningBuffer() {
  if (buffer.size() == 0) {
    charset = EncodingCharsetEnum::ASCII;
    buffer.clear();
    return;
  }
  Utf32InputStream u32is;
  Utf16InputStream u16is;
  Utf8InputStream uis(buffer);
  size_t bufferSize = buffer.size();
  if (bufferSize % 2 == 0) {
    u16is = Utf16InputStream(buffer);
  }
  if (bufferSize % 4 == 0) {
    u32is = Utf32InputStream(buffer);
  }
  detectEcsUtfBom(uis, u32is, u16is);
  if (charset != EncodingCharsetEnum::Unknown) {
    buffer.clear();
    return;
  }
  detectEcsUtf8(uis);
  if (charset != EncodingCharsetEnum::Unknown) {
    buffer.clear();
    return;
  }
  detectEcsUtf32(u32is);
  if (charset != EncodingCharsetEnum::Unknown) {
    buffer.clear();
    return;
  }
  detectEcsUtf16(u16is);
  if (charset != EncodingCharsetEnum::Unknown) {
    buffer.clear();
    return;
  }
  buffer.clear();
  charset = EncodingCharsetEnum::InvalidTextEncoding;
};

void Detector::detectEcsUtfBom(Utf8InputStream &u8is_, Utf32InputStream &u32is_,
                               Utf16InputStream &u16is_) {
  // UTF-8 BOM
  if (u8is_.readable()) {
    int32_t bom = u8is_.readByte3();
    if (CharCode::Utf8::isBom(bom)) {
      if (String::Utf8::isValidString(u8is_)) {
        charset = EncodingCharsetEnum::UTF8_BOM;
      } else {
        charset = EncodingCharsetEnum::InvalidTextEncoding;
      }
      return;
    }
  }
  // UTF-32 BOM
  if (u32is_.hasReadable()) {
    int32_t bom = u32is_.current();
    if (CharCode::Utf32::isBom(bom)) {
      if (String::Utf32::isValidString(u32is_, false)) {
        charset = EncodingCharsetEnum::UTF32BE_BOM;
      } else {
        charset = EncodingCharsetEnum::InvalidTextEncoding;
      }
      return;
    } else if (CharCode::Utf32::isBom(bom, true)) {
      if (String::Utf32::isValidString(u32is_, true)) {
        charset = EncodingCharsetEnum::UTF32LE_BOM;
      } else {
        charset = EncodingCharsetEnum::InvalidTextEncoding;
      }
      return;
    }
  }
  // UTF-16 BOM
  if (u16is_.hasReadable()) {
    int16_t bom = u16is_.current();
    if (CharCode::Utf16::isBom(bom)) {
      if (String::Utf16::isValidString(u16is_, false)) {
        charset = EncodingCharsetEnum::UTF16BE_BOM;
      } else {
        charset = EncodingCharsetEnum::InvalidTextEncoding;
      }
      return;
    } else if (CharCode::Utf16::isBom(bom, true)) {
      if (String::Utf16::isValidString(u16is_, true)) {
        charset = EncodingCharsetEnum::UTF16LE_BOM;
      } else {
        charset = EncodingCharsetEnum::InvalidTextEncoding;
      }
      return;
    }
  }
};

void Detector::detectEcsUtf8(Utf8InputStream &uis_) {
  uis_.rewind();
  if (!uis_.readable()) {
    return;
  }
  if (String::Utf8::isValidString(uis_)) {
    uis_.rewind();
    if (String::Utf8::isAsciiString(uis_)) {
      charset = EncodingCharsetEnum::ASCII;
    } else {
      charset = EncodingCharsetEnum::UTF8;
    }
    return;
  }
};

void Detector::detectEcsUtf32(Utf32InputStream &u32is_) {
  u32is_.rewind();
  if (!u32is_.readable()) {
    return;
  }
  if (String::Utf32::isValidString(u32is_, false)) {
    charset = EncodingCharsetEnum::UTF32BE;
    return;
  }
  u32is_.rewind();
  if (String::Utf32::isValidString(u32is_, true)) {
    charset = EncodingCharsetEnum::UTF32LE;
    return;
  }
};

void Detector::detectEcsUtf16(Utf16InputStream &u16is_) {
  u16is_.rewind();
  if (!u16is_.readable()) {
    return;
  }
  if (String::Utf16::isValidString(u16is_, false)) {
    charset = EncodingCharsetEnum::UTF16BE;
    return;
  }
  u16is_.rewind();
  if (String::Utf16::isValidString(u16is_, true)) {
    u16is_.rewind();
    charset = EncodingCharsetEnum::UTF16LE;
    return;
  }
};

EncodingCharsetEnum Detector::encodingCharSet() const { return charset; };
