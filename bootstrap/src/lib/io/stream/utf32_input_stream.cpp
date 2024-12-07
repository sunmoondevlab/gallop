// Copyright © 2024- Sunmoon development laboratory. All Rights Reserved.
#include "io/stream/utf32_input_stream.hpp"

#include "char_set/char_code/utf32_char_code.hpp"

using namespace gallop::IO::Stream;
using namespace gallop::CharSet;

Utf32InputStream::Utf32InputStream()
    : buffer(std::vector<int32_t>()), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
Utf32InputStream::Utf32InputStream(const std::u32string &buffer_)
    : buffer(std::vector<int32_t>(buffer_.begin(), buffer_.end())),
      bufferPtr(buffer.data()), pos(0), mark(0), bufferSize(buffer.size()) {};
Utf32InputStream::Utf32InputStream(const std::vector<char> &buffer_)
    : buffer(toByte4Buffer(buffer_)), bufferPtr(buffer.data()), pos(0), mark(0),
      bufferSize(buffer.size()) {};
std::vector<int32_t>
Utf32InputStream::toByte4Buffer(const std::vector<char> &buffer_) {
  size_t byteBufferSize = buffer_.size();
  if ((byteBufferSize % 4) > 0) {
    bufferSize = (byteBufferSize + 3) / 4;
  } else {
    bufferSize = byteBufferSize / 4;
  }
  std::vector<int32_t> byte4buffer;
  byte4buffer.reserve(bufferSize);
  const char *byteBufferPtr = buffer_.data();
  for (size_t pos = 0, bPos = 0; pos < bufferSize; pos++, bPos += 4) {
    uint32_t elm =
        (((uint32_t)*(byteBufferPtr + bPos)) << Shift3Byte) & MaskHighestByte;
    if (bPos + 1 < byteBufferSize) {
      elm |= (((uint32_t)(*(byteBufferPtr + bPos + 1)) & MaskLoe1Byte)
              << Shift2Byte);
    }
    if (bPos + 2 < byteBufferSize) {
      elm |= (((uint32_t)(*(byteBufferPtr + bPos + 2)) & MaskLoe1Byte)
              << Shift1Byte);
    }
    if (bPos + 3 < byteBufferSize) {
      elm |= ((uint32_t)(*(byteBufferPtr + bPos + 3)) & MaskLoe1Byte);
    }
    byte4buffer.push_back((int32_t)elm);
  }
  return byte4buffer;
};
Utf32InputStream::Utf32InputStream(const std::vector<int32_t> &buffer_)
    : buffer(buffer_), bufferPtr(buffer_.data()), pos(0), mark(0),
      bufferSize(buffer_.size()) {};
Utf32InputStream::Utf32InputStream(const Utf32InputStream &rhs)
    : buffer(rhs.buffer), bufferPtr(buffer.data()), pos(rhs.pos),
      mark(rhs.mark), bufferSize(rhs.bufferSize) {};
Utf32InputStream &Utf32InputStream::operator=(const Utf32InputStream &rhs) {
  buffer = rhs.buffer;
  bufferPtr = buffer.data();
  pos = rhs.pos;
  mark = rhs.mark;
  bufferSize = rhs.bufferSize;
  return *this;
};
std::vector<int32_t> &Utf32InputStream::dataRef() { return buffer; };
std::vector<int32_t> Utf32InputStream::data() { return buffer; };
int32_t Utf32InputStream::current() {
  if (hasReadable()) {
    int32_t i32 = *(bufferPtr + (pos));
    return i32;
  }
  return static_cast<int32_t>(0);
};
int32_t Utf32InputStream::read() {
  if (hasReadable()) {
    int32_t i32 = *(bufferPtr + (pos));
    pos++;
    return i32;
  }
  return static_cast<int32_t>(0);
};
int32_t Utf32InputStream::undo() {
  if (pos == 0) {
    return static_cast<int32_t>(0);
  }
  pos--;
  return *(bufferPtr + (pos));
};
int32_t Utf32InputStream::ahead() { return ahead(0ul); };
int32_t Utf32InputStream::ahead(const size_t &offset_) {
  if (readable() > (int64_t)(offset_ + 1)) {
    return *(bufferPtr + (pos + offset_ + 1));
  };
  return static_cast<int32_t>(0);
};
void Utf32InputStream::skip() {
  if (hasReadable()) {
    pos++;
  }
};
void Utf32InputStream::skip(const size_t &skipSize_) {
  size_t skipSize = skipSize_;
  size_t readableSize = readable();
  if (readableSize < skipSize) {
    skipSize = readableSize;
  }
  if (skipSize > 0) {
    pos += skipSize;
  }
};
void Utf32InputStream::markCurrent() { mark = pos; };
void Utf32InputStream::markAt(const size_t &markPos_) {
  if (markPos_ > bufferSize) {
    mark = bufferSize - 1;
  } else {
    mark = markPos_;
  }
};
void Utf32InputStream::resetMark() { mark = 0; };
void Utf32InputStream::rewind() { pos = 0; };
void Utf32InputStream::rewind(const size_t &rewindSize_) {
  if (pos >= rewindSize_) {
    pos -= rewindSize_;
  } else {
    pos = 0;
  }
};
void Utf32InputStream::rewindToMark() { pos = mark; };
bool Utf32InputStream::hasReadable() const { return bufferSize > pos; };
int64_t Utf32InputStream::readable() const {
  return bufferSize - (int64_t)(pos);
};
size_t Utf32InputStream::size() const { return bufferSize; };
size_t Utf32InputStream::currentPos() const { return pos; };
