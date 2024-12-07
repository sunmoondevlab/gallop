// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf8_input_stream.hpp"

#include "char_set/char_code/utf32_char_code.hpp"
#include "char_set/char_code/utf8_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf8InputStream::Utf8InputStream()
    : buffer(std::vector<char>()), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(0) {};
Utf8InputStream::Utf8InputStream(const std::string &buffer_)
    : buffer(std::vector<char>(buffer_.begin(), buffer_.end())),
      bufferPtr(buffer.data()), pos(0), mark(0), bufferSize(buffer.size()) {};
Utf8InputStream::Utf8InputStream(const std::vector<char> &buffer_)
    : buffer(buffer_), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
Utf8InputStream::Utf8InputStream(const Utf8InputStream &rhs)
    : buffer(rhs.buffer), bufferPtr(buffer.data()), pos(rhs.pos),
      mark(rhs.mark), bufferSize(rhs.bufferSize) {};
Utf8InputStream &Utf8InputStream::operator=(const Utf8InputStream &rhs) {
  buffer = rhs.buffer;
  bufferPtr = buffer.data();
  pos = rhs.pos;
  mark = rhs.mark;
  bufferSize = rhs.bufferSize;
  return *this;
};
std::vector<char> &Utf8InputStream::dataRef() { return buffer; };
std::vector<char> Utf8InputStream::data() { return buffer; };
int32_t Utf8InputStream::current() {
  if (hasReadable()) {
    char charCode = *(bufferPtr + (pos));
    return int32_t(uint32_t(charCode) & MaskLow1byte);
  }
  return static_cast<int32_t>(0);
};
int32_t Utf8InputStream::read() {
  if (hasReadable()) {
    char charCode = *(bufferPtr + (pos));
    pos++;
    return int32_t(uint32_t(charCode) & MaskLow1byte);
  }
  return static_cast<int32_t>(0);
};
int32_t Utf8InputStream::readByte2() {
  if (readable() >= 2) {
    uint32_t charCodeB2 = 0;
    char charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB2 = (uint32_t(charCode << ShiftByte1) & MaskLow2byte);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB2 |= (uint32_t(charCode) & MaskLow1byte);
    return int32_t(charCodeB2 & MaskLow2byte);
  }
  return static_cast<int32_t>(0);
};
int32_t Utf8InputStream::readByte3() {
  if (readable() >= 3) {
    uint32_t charCodeB3 = 0;
    char charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB3 = ((uint32_t(charCode) << ShiftByte2) & MaskLow3byte);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB3 |= ((uint32_t(charCode) & MaskLow1byte) << ShiftByte1);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB3 |= (uint32_t(charCode) & MaskLow1byte);
    return int32_t(charCodeB3);
  }
  return static_cast<int32_t>(0);
};
int32_t Utf8InputStream::readByte4() {
  if (readable() >= 4) {
    uint32_t charCodeB4 = 0;
    char charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB4 = (uint32_t)(charCode << ShiftByte3);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB4 |= ((uint32_t(charCode) & MaskLow1byte) << ShiftByte2);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB4 |= ((uint32_t(charCode) & MaskLow1byte) << ShiftByte1);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB4 |= (uint32_t(charCode) & MaskLow1byte);
    return int32_t(charCodeB4);
  }
  return static_cast<int32_t>(0);
};
int32_t Utf8InputStream::undo() {
  if (pos == 0) {
    return static_cast<int32_t>(0);
  }
  pos--;
  return int32_t(*(bufferPtr + (pos)));
};
int32_t Utf8InputStream::ahead() { return ahead(0ul); };
int32_t Utf8InputStream::ahead(const size_t &offset_) {
  if (readable() > (int64_t)(offset_ + 1)) {
    return int32_t(*(bufferPtr + (pos + offset_ + 1)));
  };
  return static_cast<int32_t>(0);
};
void Utf8InputStream::skip() {
  if (hasReadable()) {
    pos++;
  }
};
void Utf8InputStream::skip(const size_t &skipSize_) {
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  }
};
void Utf8InputStream::markCurrent() { mark = pos; };
void Utf8InputStream::markAt(const size_t &markPos_) {
  if (markPos_ > bufferSize) {
    mark = bufferSize - 1;
  } else {
    mark = markPos_;
  }
};
void Utf8InputStream::resetMark() { mark = 0; };
void Utf8InputStream::rewind() { pos = 0; };
void Utf8InputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void Utf8InputStream::rewindToMark() { pos = mark; };
bool Utf8InputStream::hasReadable() const { return bufferSize > pos; };
int64_t Utf8InputStream::readable() const {
  return bufferSize - (int64_t)(pos);
};
size_t Utf8InputStream::size() const { return bufferSize; };
size_t Utf8InputStream::currentPos() const { return pos; };
