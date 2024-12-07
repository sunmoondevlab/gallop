// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf32_output_stream.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "charset/string/utf32_string.hpp"
#include "charset/string/utf8_string.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf32OutputStream::Utf32OutputStream()
    : buffer(std::vector<int32_t>()), isSrcLE(false), isDstLE(false),
      bufferSize(0), stringLength(0) {};
Utf32OutputStream::Utf32OutputStream(const bool &isDstLE_)
    : buffer(std::vector<int32_t>()), isSrcLE(false), isDstLE(isDstLE_),
      bufferSize(0), stringLength(0) {};
Utf32OutputStream::Utf32OutputStream(const bool &isSrcLE_, const bool &isDstLE_)
    : buffer(std::vector<int32_t>()), isSrcLE(isSrcLE_), isDstLE(isDstLE_),
      bufferSize(0), stringLength(0) {};
Utf32OutputStream::Utf32OutputStream(const Utf32OutputStream &rhs)
    : buffer(rhs.buffer), isSrcLE(rhs.isSrcLE), isDstLE(rhs.isDstLE),
      bufferSize(rhs.bufferSize), stringLength(rhs.stringLength) {};
Utf32OutputStream &Utf32OutputStream::operator=(const Utf32OutputStream &rhs) {
  buffer = rhs.buffer;
  isSrcLE = rhs.isSrcLE;
  isDstLE = rhs.isDstLE;
  bufferSize = rhs.bufferSize;
  stringLength = rhs.stringLength;
  return *this;
};
void Utf32OutputStream::reserve(const size_t &size_) { buffer.reserve(size_); };
void Utf32OutputStream::write(const int32_t &charCode_) {
  bool isBom = CharCode::Utf32::isBom(charCode_, isSrcLE);
  if (isBom && bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    if (isDstLE) {
      buffer.push_back(static_cast<int32_t>(0xfdff0000));
    } else {
      buffer.push_back(static_cast<int32_t>(0x0000fffd));
    }
    bufferSize++;
    stringLength++;
    return;
  }
  if (isSrcLE != isDstLE) {
    buffer.push_back(CharCode::Utf32::swapEndianness(charCode_));
  } else {
    buffer.push_back(charCode_);
  }
  bufferSize++;
  if (!isBom) {
    stringLength++;
  }
};
void Utf32OutputStream::writeString(const std::string &string_) {
  std::vector<int32_t> chunk = String::Utf8::toUtf32Data(string_, isDstLE);
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
};
void Utf32OutputStream::reset() {
  buffer.clear();
  bufferSize = 0;
  stringLength = 0;
};
std::string Utf32OutputStream::toString() {
  return String::Utf32::toUtf8String(buffer, isDstLE);
};
std::vector<int32_t> Utf32OutputStream::data() { return buffer; };
size_t Utf32OutputStream::size() const { return bufferSize; };
size_t Utf32OutputStream::stringLen() const { return stringLength; };
