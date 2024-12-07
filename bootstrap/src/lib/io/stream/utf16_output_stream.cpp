// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf16_output_stream.hpp"

#include "char_set/char_code/utf16_char_code.hpp"
#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/string/utf16_string.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf16OutputStream::Utf16OutputStream()
    : buffer(std::vector<int16_t>()), isSrcLe(false), isDstLe(false),
      bufferSize(0), stringLength(0) {};
Utf16OutputStream::Utf16OutputStream(const bool &isDstLe_)
    : buffer(std::vector<int16_t>()), isSrcLe(false), isDstLe(isDstLe_),
      bufferSize(0), stringLength(0) {};
Utf16OutputStream::Utf16OutputStream(const bool &isSrcLe_, const bool &isDstLe_)
    : buffer(std::vector<int16_t>()), isSrcLe(isSrcLe_), isDstLe(isDstLe_),
      bufferSize(0), stringLength(0) {};
Utf16OutputStream::Utf16OutputStream(const Utf16OutputStream &rhs)
    : buffer(rhs.buffer), isSrcLe(rhs.isSrcLe), isDstLe(rhs.isDstLe),
      bufferSize(rhs.bufferSize), stringLength(rhs.stringLength) {};
Utf16OutputStream &Utf16OutputStream::operator=(const Utf16OutputStream &rhs) {
  buffer = rhs.buffer;
  isSrcLe = rhs.isSrcLe;
  isDstLe = rhs.isDstLe;
  bufferSize = rhs.bufferSize;
  stringLength = rhs.stringLength;
  return *this;
};
void Utf16OutputStream::reserve(const size_t &size_) { buffer.reserve(size_); };
void Utf16OutputStream::write(const int32_t &charCode_) {
  std::vector<int16_t> chunk;
  bool isBom = CharCode::Utf32::isBom(charCode_, isSrcLe);
  if (isBom && bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    writeReplacementChar();
    return;
  }
  if (isSrcLe != isDstLe) {
    chunk = CharCode::Utf32::toU16(CharCode::Utf32::swapEndianness(charCode_),
                                   isDstLe);
  } else {
    chunk = CharCode::Utf32::toU16(charCode_, isDstLe);
  }
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
  if (!isBom) {
    stringLength++;
  }
};
void Utf16OutputStream::writeBom() {
  if (bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    writeReplacementChar();
    return;
  }
  buffer.push_back(CharCode::Utf16::getBom(isDstLe));
  bufferSize++;
};
void Utf16OutputStream::writeReplacementChar() {
  buffer.push_back(CharCode::Utf16::getReplacementChar(isDstLe));
  bufferSize++;
  stringLength++;
};
void Utf16OutputStream::writeString(const std::u16string &u16string_) {
  std::vector<int16_t> chunk;
  if (isDstLe) {
    chunk = String::Utf16::toU16Data(
        std::vector<int16_t>(u16string_.begin(), u16string_.end()), false, true,
        false);
  } else {
    chunk = String::Utf16::toU16Data(
        std::vector<int16_t>(u16string_.begin(), u16string_.end()));
  }
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
};
void Utf16OutputStream::reset() {
  buffer.clear();
  bufferSize = 0;
  stringLength = 0;
};
std::u16string Utf16OutputStream::toU16String() {
  std::vector<int16_t> beBuffer;
  if (isDstLe) {
    beBuffer = String::Utf16::toU16Data(buffer, true, false, false);
  } else {
    beBuffer = buffer;
  }
  Utf16InputStream uis(beBuffer);
  if (uis.size() >= 1 && CharCode::Utf16::isBom(uis.read())) {
    return std::u16string(beBuffer.begin() + 1, beBuffer.end());
  }
  return std::u16string(beBuffer.begin(), beBuffer.end());
};
std::vector<int16_t> Utf16OutputStream::data() { return buffer; };
size_t Utf16OutputStream::size() const { return bufferSize; };
size_t Utf16OutputStream::stringLen() const { return stringLength; };
