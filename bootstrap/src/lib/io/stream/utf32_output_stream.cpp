// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf32_output_stream.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/string/utf32_string.hpp"
#include "char_set/string/utf8_string.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf32OutputStream::Utf32OutputStream()
    : buffer(std::vector<int32_t>()), isSrcLe(false), isDstLe(false),
      bufferSize(0), stringLength(0) {};
Utf32OutputStream::Utf32OutputStream(const bool &isDstLe_)
    : buffer(std::vector<int32_t>()), isSrcLe(false), isDstLe(isDstLe_),
      bufferSize(0), stringLength(0) {};
Utf32OutputStream::Utf32OutputStream(const bool &isSrcLe_, const bool &isDstLe_)
    : buffer(std::vector<int32_t>()), isSrcLe(isSrcLe_), isDstLe(isDstLe_),
      bufferSize(0), stringLength(0) {};
Utf32OutputStream::Utf32OutputStream(const Utf32OutputStream &rhs)
    : buffer(rhs.buffer), isSrcLe(rhs.isSrcLe), isDstLe(rhs.isDstLe),
      bufferSize(rhs.bufferSize), stringLength(rhs.stringLength) {};
Utf32OutputStream &Utf32OutputStream::operator=(const Utf32OutputStream &rhs) {
  buffer = rhs.buffer;
  isSrcLe = rhs.isSrcLe;
  isDstLe = rhs.isDstLe;
  bufferSize = rhs.bufferSize;
  stringLength = rhs.stringLength;
  return *this;
};
void Utf32OutputStream::reserve(const size_t &size_) { buffer.reserve(size_); };
void Utf32OutputStream::write(const int32_t &charCode_) {
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
    buffer.push_back(CharCode::Utf32::swapEndianness(charCode_));
  } else {
    buffer.push_back(charCode_);
  }
  bufferSize++;
  if (!isBom) {
    stringLength++;
  }
};
void Utf32OutputStream::writeBom() {
  if (bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    writeReplacementChar();
    return;
  }
  buffer.push_back(CharCode::Utf32::getBom(isDstLe));
  bufferSize++;
};
void Utf32OutputStream::writeReplacementChar() {
  buffer.push_back(CharCode::Utf32::getReplacementChar(isDstLe));
  bufferSize++;
  stringLength++;
};
void Utf32OutputStream::writeString(const std::u32string &u32string_) {
  std::vector<int32_t> chunk;
  if (isDstLe) {
    chunk = String::Utf32::toU32Data(
        std::vector<int32_t>(u32string_.begin(), u32string_.end()), false, true,
        false);
  } else {
    chunk = String::Utf32::toU32Data(
        std::vector<int32_t>(u32string_.begin(), u32string_.end()));
  }
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
};
void Utf32OutputStream::reset() {
  buffer.clear();
  bufferSize = 0;
  stringLength = 0;
};
std::u32string Utf32OutputStream::toU32String() {
  std::vector<int32_t> beBuffer;
  if (isDstLe) {
    beBuffer = String::Utf32::toU32Data(buffer, true, false, false);
  } else {
    beBuffer = buffer;
  }
  Utf32InputStream uis(beBuffer);
  if (uis.size() >= 1 && CharCode::Utf32::isBom(uis.read())) {
    return std::u32string(beBuffer.begin() + 1, beBuffer.end());
  }
  return std::u32string(beBuffer.begin(), beBuffer.end());
};
std::vector<int32_t> Utf32OutputStream::data() { return buffer; };
size_t Utf32OutputStream::size() const { return bufferSize; };
size_t Utf32OutputStream::stringLen() const { return stringLength; };
