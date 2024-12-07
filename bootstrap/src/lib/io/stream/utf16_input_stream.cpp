// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf16_input_stream.hpp"

#include "char_set/char_code/utf32_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf16InputStream::Utf16InputStream()
    : buffer(std::vector<int16_t>()), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
Utf16InputStream::Utf16InputStream(const std::u16string &buffer_)
    : buffer(std::vector<int16_t>(buffer_.begin(), buffer_.end())),
      bufferPtr(buffer.data()), pos(0), mark(0), bufferSize(buffer.size()) {};
Utf16InputStream::Utf16InputStream(const std::vector<char> &buffer_)
    : buffer(toByte2Buffer(buffer_)), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
std::vector<int16_t>
Utf16InputStream::toByte2Buffer(const std::vector<char> &buffer_) {
  size_t byteBufferSize = buffer_.size();
  if ((byteBufferSize % 2) > 0) {
    bufferSize = (byteBufferSize + 1) / 2;
  } else {
    bufferSize = byteBufferSize / 2;
  }
  std::vector<int16_t> byte2buffer;
  byte2buffer.reserve(bufferSize);
  const char *byteBufferPtr = buffer_.data();
  for (size_t pos = 0, bPos = 0; pos < bufferSize; pos++, bPos += 2) {
    uint16_t elm = (((uint16_t)*(byteBufferPtr + bPos)) << ShiftByte1) &
                   MaskByte2High1Byte;
    if (bPos + 1 < byteBufferSize) {
      elm |= ((uint16_t)(*(byteBufferPtr + bPos + 1)) & MaskByte2Low1Byte);
    }
    byte2buffer.push_back((int16_t)elm);
  }
  return byte2buffer;
};
Utf16InputStream::Utf16InputStream(const std::vector<int16_t> &buffer_)
    : buffer(buffer_), bufferPtr(buffer_.data()), pos(0), mark(0),
      bufferSize(buffer_.size()) {};
Utf16InputStream::Utf16InputStream(const Utf16InputStream &rhs)
    : buffer(rhs.buffer), bufferPtr(buffer.data()), pos(rhs.pos),
      mark(rhs.mark), bufferSize(rhs.bufferSize) {};
Utf16InputStream &Utf16InputStream::operator=(const Utf16InputStream &rhs) {
  buffer = rhs.buffer;
  bufferPtr = buffer.data();
  pos = rhs.pos;
  mark = rhs.mark;
  bufferSize = rhs.bufferSize;
  return *this;
};
std::vector<int16_t> &Utf16InputStream::dataRef() { return buffer; };
std::vector<int16_t> Utf16InputStream::data() { return buffer; };
int16_t Utf16InputStream::current() {
  if (hasReadable()) {
    int16_t charCode = *(bufferPtr + (pos));
    return charCode;
  }
  return static_cast<int16_t>(0);
};
int16_t Utf16InputStream::read() {
  if (hasReadable()) {
    int16_t charCode = *(bufferPtr + (pos));
    pos++;
    return charCode;
  }
  return static_cast<int16_t>(0);
};
int32_t Utf16InputStream::readByte4() {
  if (readable() >= 2) {
    uint32_t charCodeB4 = 0;
    int16_t charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB4 = (uint32_t)(charCode << ShiftByte2);
    charCode = *(bufferPtr + (pos));
    pos++;
    charCodeB4 |= ((uint32_t)(charCode)&MaskByte4Low2Byte);
    return (int32_t)charCodeB4;
  }
  return static_cast<int32_t>(0);
};
int16_t Utf16InputStream::undo() {
  if (pos == 0) {
    return static_cast<int16_t>(0);
  }
  pos--;
  return *(bufferPtr + (pos));
};
int16_t Utf16InputStream::ahead() { return ahead(0ul); };
int16_t Utf16InputStream::ahead(const size_t &offset_) {
  if (readable() > (int64_t)(offset_ + 1)) {
    return *(bufferPtr + (pos + offset_ + 1));
  };
  return static_cast<int16_t>(0);
};
void Utf16InputStream::skip() {
  if (hasReadable()) {
    pos++;
  }
};
void Utf16InputStream::skip(const size_t &skipSize_) {
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  }
};
void Utf16InputStream::markCurrent() { mark = pos; };
void Utf16InputStream::markAt(const size_t &markPos_) {
  if (markPos_ > bufferSize) {
    mark = bufferSize - 1;
  } else {
    mark = markPos_;
  }
};
void Utf16InputStream::resetMark() { mark = 0; };
void Utf16InputStream::rewind() { pos = 0; };
void Utf16InputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void Utf16InputStream::rewindToMark() { pos = mark; };
bool Utf16InputStream::hasReadable() const { return bufferSize > pos; };
int64_t Utf16InputStream::readable() const {
  return bufferSize - (int64_t)(pos);
};
size_t Utf16InputStream::size() const { return bufferSize; };
size_t Utf16InputStream::currentPos() const { return pos; };
