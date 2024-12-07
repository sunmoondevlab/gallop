// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf16_output_stream.hpp"
#include "charset/char_code/utf32_char_code.hpp"
#include "charset/string/utf16_string.hpp"
#include "charset/string/utf8_string.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf16OutputStream::Utf16OutputStream()
    : buffer(std::vector<int16_t>()), isSrcLE(false), isDstLE(false),
      bufferSize(0), stringLength(0) {};
Utf16OutputStream::Utf16OutputStream(const bool &isDstLE_)
    : buffer(std::vector<int16_t>()), isSrcLE(false), isDstLE(isDstLE_),
      bufferSize(0), stringLength(0) {};
Utf16OutputStream::Utf16OutputStream(const bool &isSrcLE_, const bool &isDstLE_)
    : buffer(std::vector<int16_t>()), isSrcLE(isSrcLE_), isDstLE(isDstLE_),
      bufferSize(0), stringLength(0) {};
Utf16OutputStream::Utf16OutputStream(const Utf16OutputStream &rhs)
    : buffer(rhs.buffer), isSrcLE(rhs.isSrcLE), isDstLE(rhs.isDstLE),
      bufferSize(rhs.bufferSize), stringLength(rhs.stringLength) {};
Utf16OutputStream &Utf16OutputStream::operator=(const Utf16OutputStream &rhs) {
  buffer = rhs.buffer;
  isSrcLE = rhs.isSrcLE;
  isDstLE = rhs.isDstLE;
  bufferSize = rhs.bufferSize;
  stringLength = rhs.stringLength;
  return *this;
};
void Utf16OutputStream::reserve(const size_t &size_) { buffer.reserve(size_); };
void Utf16OutputStream::write(const int32_t &charCode_) {
  std::vector<int16_t> chunk;
  bool isBom = CharCode::Utf32::isBom(charCode_, isSrcLE);
  if (isBom && bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    if (isDstLE) {
      chunk = {
          static_cast<int16_t>(0xfdff),
      };
    } else {
      chunk = {
          static_cast<int16_t>(0xfffd),
      };
    }
    std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
    bufferSize++;
    stringLength++;
    return;
  }
  if (isSrcLE != isDstLE) {
    chunk = CharCode::Utf32::toUtf16Chunk(
        CharCode::Utf32::swapEndianness(charCode_), isDstLE);
  } else {
    chunk = CharCode::Utf32::toUtf16Chunk(charCode_, isDstLE);
  }
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
  if (!isBom) {
    stringLength++;
  }
};
void Utf16OutputStream::writeString(const std::string &string_) {
  std::vector<int16_t> chunk = String::Utf8::toUtf16Data(string_, isDstLE);
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
};
void Utf16OutputStream::reset() {
  buffer.clear();
  bufferSize = 0;
  stringLength = 0;
};
std::string Utf16OutputStream::toString() {
  return String::Utf16::toUtf8String(buffer, isDstLE);
};
std::vector<int16_t> Utf16OutputStream::data() { return buffer; };
size_t Utf16OutputStream::size() const { return bufferSize; };
size_t Utf16OutputStream::stringLen() const { return stringLength; };
