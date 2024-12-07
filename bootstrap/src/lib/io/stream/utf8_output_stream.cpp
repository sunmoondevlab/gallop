// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf8_output_stream.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"
#include "io/stream/utf8_input_stream.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf8OutputStream::Utf8OutputStream()
    : buffer(std::vector<char>()), bufferSize(0), stringLength(0) {};
Utf8OutputStream::Utf8OutputStream(const Utf8OutputStream &rhs)
    : buffer(rhs.buffer), bufferSize(rhs.bufferSize),
      stringLength(rhs.stringLength) {};

Utf8OutputStream &Utf8OutputStream::operator=(const Utf8OutputStream &rhs) {
  buffer = rhs.buffer;
  bufferSize = rhs.bufferSize;
  stringLength = rhs.stringLength;
  return *this;
};
void Utf8OutputStream::reserve(const size_t &size_) { buffer.reserve(size_); };
void Utf8OutputStream::write(const int32_t &charCode_) {
  std::vector<char> chunk;
  bool isBom = CharCode::Utf32::isBom(charCode_);
  if (isBom && bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    writeReplacementChar();
    return;
  }
  chunk = CharCode::Utf32::toU8(charCode_);
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
  if (!isBom) {
    stringLength++;
  }
};
void Utf8OutputStream::writeBom() {
  if (bufferSize > 0) {
    if (stringLength == 0) {
      // consecutive bom
      return;
    }
    writeReplacementChar();
    return;
  }
  std::vector<char> chunk = CharCode::Utf8::getBomChunk();
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
};
void Utf8OutputStream::writeReplacementChar() {
  std::vector<char> chunk = CharCode::Utf8::getReplacementCharChunk();
  size_t chunkSize = chunk.size();
  std::copy(chunk.begin(), chunk.end(), std::back_inserter(buffer));
  bufferSize += chunkSize;
  stringLength++;
};
void Utf8OutputStream::writeString(const std::string &string_) {
  size_t stringSize = string_.size();
  std::copy(string_.begin(), string_.end(), std::back_inserter(buffer));
  bufferSize += stringSize;
};
void Utf8OutputStream::reset() {
  buffer.clear();
  bufferSize = 0;
  stringLength = 0;
};
std::string Utf8OutputStream::toU8String() {
  Utf8InputStream uis(buffer);
  if (uis.size() >= 3 && CharCode::Utf8::isBom(uis.readByte3())) {
    return std::string(buffer.begin() + 3, buffer.end());
  }
  return std::string(buffer.begin(), buffer.end());
};
std::vector<char> Utf8OutputStream::data() { return buffer; };
size_t Utf8OutputStream::size() const { return bufferSize; };
size_t Utf8OutputStream::stringLen() const { return stringLength; };
